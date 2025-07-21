// MySingleton.hpp
#pragma once
#include <BaiduFaceID/BaiduFaceID.h>
#include <functional>
#include <lvgl.h>
#include <string>
#include <sys/wait.h>
#include <thread>
#include <unordered_map>

#define lot lv_obj_t *

class Base
{
  public:
    static Base &instance()
    {
        static Base _instance;
        return _instance;
    }

  private:
    Base() = default;
    ~Base() = default;
    Base(const Base &) = delete;
    Base &operator=(const Base &) = delete;

    pid_t camera_stream_pid = -1;                         // 摄像头推流子进程的 PID
    std::unordered_map<int, lv_font_t *> font_map;        // 字号到字体对象的映射
    std::string camera_stream_url = "tcp://0.0.0.0:8988"; // 摄像头推流的默认URL

    //----------------------内部工具函数----------------------
  private:
    static void stop_camera_stream();

    //----------------------公开函数----------------------
  public:
    BaiduFaceID *face_service = nullptr;
    void register_atexit();
    void start_camera_stream_impl();
    void stop_camera_stream_impl();

    // 在后台线程中执行拍照操作
    void capture_photo_async(const std::string &filename = "/tmp/captured_photo.jpg", std::function<void(bool, const std::string &)> callback = nullptr);

    std::string get_camera_stream_url() const;
    void set_camera_stream_url(const std::string &url);

    // 获取指定字号的字体对象，如果没有则创建
    lv_font_t *getFont(int size);

    // 可选：释放所有字体对象（如果需要手动释放）
    void clearFonts();
};


// 函数实现
static void mask_corner_side(lv_obj_t *parent, bool mask_left_side)
{
    lv_obj_set_style_clip_corner(parent, true, 0);
    lv_obj_t *mask_rect = lv_obj_create(parent);
    lv_obj_set_size(mask_rect, lv_pct(100), lv_pct(100));
    lv_obj_remove_style_all(mask_rect);
    lv_obj_set_style_border_width(mask_rect, 15, 0);
    lv_obj_set_style_border_color(mask_rect, lv_obj_get_style_bg_color(parent, 0), 0);
    if (mask_left_side) {
        lv_obj_set_style_border_side(mask_rect, LV_BORDER_SIDE_LEFT, 0);
    } else {
        lv_obj_set_style_border_side(mask_rect, LV_BORDER_SIDE_RIGHT, 0);
    }
}