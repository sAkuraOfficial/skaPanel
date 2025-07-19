/*
 * 
 *
 * 功能:
 * TOKEN
 * TOKEN
 * TOKEN
 *
 * TOKEN
 * TOKEN
 */

#include <signal.h> // For kill signal constants
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> // For pid_t
#include <unistd.h>    // For fork, execlp, kill, sleep

#include "lvgl/lvgl.h"

// 添加文件资源管理器相关头文件

#include "lvgl/src/libs/ffmpeg/lv_ffmpeg.h"
#include "main.hpp"
#include "src/base/base.hpp"
#include "src/lib/driver_backends.h"
#include "src/lib/simulator_util.h"
lv_obj_t *img = nullptr;

static void tabview_event_cb(lv_event_t *e)
{
    lv_obj_t *tv = (lv_obj_t *)lv_event_get_target(e);
    uint16_t tab_idx = lv_tabview_get_tab_act(tv);

    // 假设摄像头在第0页
    if (tab_idx != 0 && img != nullptr)
    {
        lv_ffmpeg_player_set_cmd(img, LV_FFMPEG_PLAYER_CMD_STOP);
        printf("摄像头播放器已停止\n");
    }
    // 如果切回摄像头页，可以继续播放
    else if (tab_idx == 0 && img != nullptr)
    {
        lv_ffmpeg_player_set_cmd(img, LV_FFMPEG_PLAYER_CMD_START);
        printf("摄像头播放器已恢复播放\n");
    }
}

int main()
{
    // --- LVGL 初始化 ---
    Base &base = Base::instance();
    // 设置推流链接
    printf("等待摄像头推流启动...\n");
    base.set_camera_stream_url("tcp://0.0.0.0:8988");
    base.register_atexit(); // 注册退出时清理摄像头推流
    base.start_camera_stream_impl();
    sleep(2);
    printf("摄像头推流已启动，URL: %s\n", base.get_camera_stream_url().c_str());

    lv_init();
    driver_backends_register();
    /* Initialize framebuffer backend */
    if (driver_backends_init_backend("FBDEV") == -1)
    {
        die("Failed to initialize framebuffer backend");
    }
    if (driver_backends_init_backend("EVDEV") == -1)
    {
        die("Failed to initialize evdev");
    }
    // 创建字体样式

    lv_theme_t *theme = lv_theme_default_init(NULL, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, base.getFont(32)); // 这里传入你想要的字体
    lv_disp_set_theme(NULL, theme);                                                                                                              // NULL 表示当前默认显示器

    lv_coord_t screen_width = lv_obj_get_width(lv_screen_active());
    lv_coord_t screen_height = lv_obj_get_height(lv_screen_active());
    lv_obj_clear_flag(lv_screen_active(), LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t *tv = lv_tabview_create(lv_screen_active()); // 创建一个标签视图
    lv_obj_t *t1 = lv_tabview_add_tab(tv, "人脸录入");
    lv_obj_t *t2 = lv_tabview_add_tab(tv, "Analytics");
    lv_obj_t *t3 = lv_tabview_add_tab(tv, "Shop");

    lv_obj_t *label1 = lv_label_create(t1);
    lv_label_set_text(label1, "测试摄像头!");
    lv_obj_set_style_text_font(label1, base.getFont(88), 0);
    lv_obj_set_style_border_width(label1, 1, 0);
    lv_obj_get_style_border_color(label1, 0xff1234);

    // --- 创建并配置 FFmpeg 播放器 ---
    img = lv_ffmpeg_player_create(t1);
    lv_ffmpeg_player_set_src(img, base.get_camera_stream_url().c_str());     // 设置视频源为摄像头推流 URL
    lv_ffmpeg_player_set_cmd(img, LV_FFMPEG_PLAYER_CMD_START);               // 启动播放器
    lv_obj_add_event_cb(tv, tabview_event_cb, LV_EVENT_VALUE_CHANGED, NULL); // 添加事件回调以处理标签切换
    lv_obj_set_style_border_width(img, 1, 0);
    lv_obj_get_style_border_color(img, 0xff1234);
    lv_obj_align_to(img, label1, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 20);

    //--------------------------------------------------------------------
    {
        info_contaner = lv_obj_create(t1);
        lv_obj_set_size(info_contaner, 980, 1300);
        lv_color_t color_temp = {111, 222, 111};
        lv_obj_set_style_bg_color(info_contaner, color_temp, 0);
        int x = lv_obj_get_x(img) + lv_obj_get_width(img) + 50;
        int y = lv_obj_get_y(label1);
        lv_obj_set_pos(info_contaner, x, y);

        // 创建tabview组件
        info_tableView = lv_tabview_create(info_contaner);
        page1 = lv_tabview_add_tab(info_tableView, "登录");
        page2 = lv_tabview_add_tab(info_tableView, "注册");

        // 为page1添加组件
        lv_obj_set_flex_flow(page1, LV_FLEX_FLOW_COLUMN);
        label_name_show = lv_label_create(page1);
        lv_label_set_text_fmt(label_name_show, "识别结果：%s", face_name.c_str());
        // lv_style_t style;
        // lv_style_init(&style);
        // lv_style_set_margin_bottom(&style, 20);
        // lv_obj_add_style(label_name_show, &style, 0);
        button_check_face = lv_btn_create(page1);
        button_check_face_label = lv_label_create(button_check_face);
        lv_obj_set_size(button_check_face, 200, 100);
        lv_label_set_text(button_check_face_label, "识别一下");
        // 绑定点击事件
        lv_obj_add_event_cb(
            button_check_face,
            [](lv_event_t *e) {
                lv_event_code_t code = lv_event_get_code(e);
                if (code == LV_EVENT_CLICKED)
                {
                    face_name = "按钮被点击了";
                    lv_label_set_text_fmt(label_name_show, "识别结果：%s", face_name.c_str());
                }
            },
            LV_EVENT_ALL,
            NULL
        );
        lv_obj_center(button_check_face_label);
    }

    // --- LVGL 主循环 ---
    driver_backends_run_loop();

    return 0;
}
