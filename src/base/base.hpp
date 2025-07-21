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

    inline void setFontToObj(lv_obj_t *obj, int size)
    {
        if (!obj)
            return;
        lv_font_t *font = getFont(size);
        if (font)
        {
            lv_obj_set_style_text_font(obj, font, 0);
        }
    }

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
    if (mask_left_side)
    {
        lv_obj_set_style_border_side(mask_rect, LV_BORDER_SIDE_LEFT, 0);
    }
    else
    {
        lv_obj_set_style_border_side(mask_rect, LV_BORDER_SIDE_RIGHT, 0);
    }
}

static void set_obj_no_bg_no_border(lv_obj_t *obj)
{
    lv_obj_set_style_bg_opa(obj, LV_OPA_TRANSP, 0);     // 背景透明
    lv_obj_set_style_border_opa(obj, LV_OPA_TRANSP, 0); // 边框透明
    lv_obj_set_style_radius(obj, 0, 0);                 // 无圆角
    lv_obj_set_style_shadow_width(obj, 0, 0);           // 无阴影
}

/**
 * 创建圆形社交登录按钮
 * @param parent 父容器
 * @param icon_path 图标路径
 * @param size 按钮大小
 * @param border_color 边框颜色（16进制）
 * @param border_width 边框宽度
 * @param border_opa 边框透明度
 * @return 返回创建的按钮对象
 */
static lv_obj_t *create_social_login_button(lv_obj_t *parent, const char *icon_path, int32_t size = 45, uint32_t border_color = 0xbfc3c7, int32_t border_width = 4, lv_opa_t border_opa = 200)
{
    // 创建按钮
    lv_obj_t *btn = lv_btn_create(parent);

    // 创建按钮图标
    lv_obj_t *img = lv_img_create(btn);
    lv_img_set_src(img, icon_path);                        // 设置图标路径
    lv_obj_set_size(img, size-10, size-10);                      // 设置图标大小
    lv_image_set_inner_align(img, LV_IMAGE_ALIGN_CONTAIN); // 开启图片自适应缩放
    lv_obj_center(img);                                    // 图标居中

    // 设置按钮样式
    lv_obj_set_size(btn, size, size);                                  // 设置宽高相等
    lv_obj_set_style_radius(btn, LV_RADIUS_CIRCLE, 0);                 // 设置圆角为最大
    lv_obj_set_style_bg_opa(btn, LV_OPA_0, 0);                         // 背景透明
    lv_obj_set_style_border_opa(btn, border_opa, 0);                   // 边框透明度
    lv_obj_set_style_border_color(btn, lv_color_hex(border_color), 0); // 设置边框颜色
    lv_obj_set_style_border_width(btn, border_width, 0);               // 设置边框宽度

    return btn;
}