#pragma once
#include <string>
#include <functional>
#include <optional>
#include <vector>
#include <nlohmann/json.hpp>
#include <fstream>
#include <vector>
#include <string>
#include <cstdint>
#include <stdexcept>
class BaiduFaceID
{
public:
    BaiduFaceID(const std::string &apiKey, const std::string &secretKey);

    // 人脸图片用二进制（jpg/png的原始内容）传入
    void registerUser(
        const std::string &userId,
        const std::vector<uint8_t> &faceImage,
        std::function<void(const std::string &userId)> onSuccess,
        std::function<void(const std::string &errorStr)> onFailed);

    void login(
        const std::vector<uint8_t> &faceImage,
        std::function<void(const std::string &userId)> onSuccess,
        std::function<void(const std::string &errorStr)> onFailed);

    void checkIdExist(
        const std::string &userId,
        std::function<void(bool exist)> onResult);

    void checkFaceExist(
        const std::vector<uint8_t> &faceImage,
        std::function<void(bool exist)> onResult);

private:
    void fetchAccessToken();
    bool ensureTokenReady();

    // 内部同步调用
    bool postJson(const std::string &url, const std::string &postBody, nlohmann::json &jsonResp, std::string &errMsg);
    std::string base64Encode(const std::vector<uint8_t> &data);
    std::string m_apiKey;
    std::string m_secretKey;
    std::string m_groupId = "image";
    std::string m_accessToken;
    long long m_tokenExpireEpoch = 0;
};
inline std::vector<uint8_t> loadImageAsBytes(const std::string &path)
{
    std::ifstream file(path, std::ios::binary);
    if (!file)
        throw std::runtime_error("无法打开文件: " + path);
    // 获取文件长度
    file.seekg(0, std::ios::end);
    size_t len = file.tellg();
    file.seekg(0, std::ios::beg);
    // 读取内容
    std::vector<uint8_t> data(len);
    if (len > 0)
        file.read(reinterpret_cast<char *>(data.data()), len);
    return data;
}