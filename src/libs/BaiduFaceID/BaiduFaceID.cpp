#include "BaiduFaceID.h"
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <chrono>
#include <thread>
#include <sstream>
#include <iomanip>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>

// base64编码，用openssl
std::string BaiduFaceID::base64Encode(const std::vector<uint8_t>& data) {
    BIO* b64 = BIO_new(BIO_f_base64());
    BIO* mem = BIO_new(BIO_s_mem());
    b64 = BIO_push(b64, mem);
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    BIO_write(b64, data.data(), static_cast<int>(data.size()));
    BIO_flush(b64);
    BUF_MEM* memPtr;
    BIO_get_mem_ptr(b64, &memPtr);
    std::string ret(memPtr->data, memPtr->length);
    BIO_free_all(b64);
    return ret;
}

// url encode
static std::string urlEncode(const std::string& value) {
    std::ostringstream escaped;
    escaped.fill('0');
    escaped << std::hex;
    for (char c : value) {
        if (isalnum((unsigned char)c) || c == '-' || c == '_' || 
            c == '.' || c == '~') 
        {
            escaped << c;
        } else {
            escaped << '%' << std::setw(2) << int((unsigned char)c);
        }
    }
    return escaped.str();
}

BaiduFaceID::BaiduFaceID(const std::string& apiKey, const std::string& secretKey)
    : m_apiKey(apiKey), m_secretKey(secretKey) {
    fetchAccessToken();
}

void BaiduFaceID::fetchAccessToken() {
    std::string url = "https://aip.baidubce.com/oauth/2.0/token";
    cpr::Response r = cpr::Get(
        cpr::Url{url},
        cpr::Parameters{
            {"grant_type", "client_credentials"},
            {"client_id", m_apiKey},
            {"client_secret", m_secretKey}
        }
    );
    if (r.status_code != 200) {
        throw std::runtime_error("Network error: " + r.error.message);
    }
    nlohmann::json j = nlohmann::json::parse(r.text, nullptr, false);
    if (!j.contains("access_token")) {
        throw std::runtime_error("Get access_token failed: " + r.text);
    }
    m_accessToken = j["access_token"].get<std::string>();
    int expires_in = j.value("expires_in", 0);
    m_tokenExpireEpoch = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) + expires_in - 600;
}

bool BaiduFaceID::ensureTokenReady() {
    if (m_accessToken.empty() || std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) > m_tokenExpireEpoch) {
        try {
            fetchAccessToken();
        } catch (...) {
            return false;
        }
    }
    return true;
}

bool BaiduFaceID::postJson(const std::string& url, const std::string& postBody, nlohmann::json& jsonResp, std::string& errMsg) {
    cpr::Response r = cpr::Post(
        cpr::Url{url},
        cpr::Header{{"Content-Type", "application/json"}},
        cpr::Body{postBody}
    );
    if (r.status_code != 200) {
        errMsg = "HTTP error: " + std::to_string(r.status_code);
        return false;
    }
    jsonResp = nlohmann::json::parse(r.text, nullptr, false);
    if (!jsonResp.is_object()) {
        errMsg = "JSON parse failed";
        return false;
    }
    return true;
}

void BaiduFaceID::registerUser(
    const std::string& userId, 
    const std::vector<uint8_t>& faceImage, 
    std::function<void(const std::string& userId)> onSuccess,
    std::function<void(const std::string& errorStr)> onFailed) 
{
    if (!ensureTokenReady()) {
        onFailed("Access token unavailable.");
        return;
    }
    std::string url = "https://aip.baidubce.com/rest/2.0/face/v3/faceset/user/add?access_token=" + m_accessToken;
    nlohmann::json payload = {
        {"image", base64Encode(faceImage)},
        {"image_type", "BASE64"},
        {"group_id", m_groupId},
        {"user_id", userId}
    };
    nlohmann::json resp; std::string err;
    if (!postJson(url, payload.dump(), resp, err)) {
        onFailed(err);
        return;
    }
    if (resp.value("error_code", 0) == 0) {
        if (onSuccess) onSuccess(userId);
    } else {
        onFailed(resp.value("error_msg", "unknown error"));
    }
}

void BaiduFaceID::login(
    const std::vector<uint8_t>& faceImage, 
    std::function<void(const std::string& userId)> onSuccess,
    std::function<void(const std::string& errorStr)> onFailed) 
{
    if (!ensureTokenReady()) {
        onFailed("Access token unavailable.");
        return;
    }
    std::string url = "https://aip.baidubce.com/rest/2.0/face/v3/search?access_token=" + m_accessToken;
    nlohmann::json payload = {
        {"image", base64Encode(faceImage)},
        {"image_type", "BASE64"},
        {"group_id_list", m_groupId}
    };
    nlohmann::json resp; std::string err;
    if (!postJson(url, payload.dump(), resp, err)) {
        onFailed(err);
        return;
    }
    if (resp.value("error_code", 0) == 0) {
        auto result = resp["result"];
        if (result.contains("user_list") && !result["user_list"].empty()) {
            auto user_list = result["user_list"];
            std::string user_id = user_list[0]["user_id"];
            float score = user_list[0].value("score", 0.0f);
            if (score > 80.0f) {
                if (onSuccess) onSuccess(user_id);
            } else {
                onFailed("Login failed: score too low.");
            }
        } else {
            onFailed("No matching face found.");
        }
    } else {
        onFailed(resp.value("error_msg", "unknown error"));
    }
}

void BaiduFaceID::checkIdExist(
    const std::string& userId, 
    std::function<void(bool exist)> onResult) 
{
    if (!ensureTokenReady()) {
        onResult(false);
        return;
    }
    std::string url = "https://aip.baidubce.com/rest/2.0/face/v3/faceset/user/get?access_token=" + m_accessToken;
    nlohmann::json payload = {
        {"user_id", userId},
        {"group_id", m_groupId}
    };
    nlohmann::json resp; std::string err;
    if (!postJson(url, payload.dump(), resp, err)) {
        onResult(false);
        return;
    }
    if (resp.value("error_code", 0) == 0) {
        auto result = resp["result"];
        if (result.contains("user_list") && !result["user_list"].empty()) {
            onResult(true);
        } else {
            onResult(false);
        }
    } else {
        onResult(false);
    }
}

void BaiduFaceID::checkFaceExist(
    const std::vector<uint8_t>& faceImage, 
    std::function<void(bool exist)> onResult)
{
    if (!ensureTokenReady()) {
        onResult(false);
        return;
    }
    std::string url = "https://aip.baidubce.com/rest/2.0/face/v3/search?access_token=" + m_accessToken;
    nlohmann::json payload = {
        {"image", base64Encode(faceImage)},
        {"image_type", "BASE64"},
        {"group_id_list", m_groupId}
    };
    nlohmann::json resp; std::string err;
    if (!postJson(url, payload.dump(), resp, err)) {
        onResult(false);
        return;
    }
    if (resp.value("error_code", 0) == 0) {
        auto result = resp["result"];
        if (result.contains("user_list") && !result["user_list"].empty()) {
            float score = result["user_list"][0].value("score", 0.0);
            if (score > 80.0f)
                onResult(true);
            else
                onResult(false);
        } else {
            onResult(false);
        }
    } else {
        onResult(false);
    }
}
