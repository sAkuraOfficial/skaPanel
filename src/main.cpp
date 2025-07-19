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
#include "lvgl/examples/lv_examples.h"
#include "lvgl/src/indev/lv_indev.h"
#include "lvgl/src/others/file_explorer/lv_file_explorer.h"

#include "lvgl/src/libs/ffmpeg/lv_ffmpeg.h"
#include "src/base/base.hpp"
#include "src/lib/driver_backends.h"
#include "src/lib/simulator_util.h"

int main()
{
    // --- LVGL 初始化 ---
    Base &base = Base::instance();
    //设置推流链接
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
    static lv_style_t style_global;
    lv_style_init(&style_global);
    lv_style_set_text_font(&style_global, base.getFont(88));
    // 应用到全局
    lv_obj_add_style(lv_screen_active(), &style_global, 0);

    lv_coord_t screen_width = lv_obj_get_width(lv_screen_active());
    lv_coord_t screen_height = lv_obj_get_height(lv_screen_active());
    lv_obj_clear_flag(lv_screen_active(), LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t *tv = lv_tabview_create(lv_screen_active()); // 创建一个标签视图
    lv_obj_t *t1 = lv_tabview_add_tab(tv, "Profile");
    lv_obj_t *t2 = lv_tabview_add_tab(tv, "Analytics");
    lv_obj_t *t3 = lv_tabview_add_tab(tv, "Shop");

    lv_obj_t *label1 = lv_label_create(t1);
    lv_label_set_text(label1, "测试摄像头!");
    lv_obj_set_style_text_font(label1, base.getFont(88), 0);
    lv_obj_align(label1, LV_ALIGN_TOP_MID, 0, 20); // 居中对齐标签

    // --- 创建并配置 FFmpeg 播放器 ---
    lv_obj_t *img = lv_ffmpeg_player_create(t1);

    // 将播放器放置在标签下方
    // 注意: 原代码中的 button1 未定义，这里改为相对于父对象 t1 对齐
    lv_obj_align(img, LV_ALIGN_CENTER, 0, 40);

    // 设置播放源为本地 TCP 流
    lv_ffmpeg_player_set_src(img, base.get_camera_stream_url().c_str());

    // 开始播放
    lv_ffmpeg_player_set_cmd(img, LV_FFMPEG_PLAYER_CMD_START);

    // lv_obj_set_style_transform_angle(img, 180, 0);

    // --- LVGL 主循环 ---
    driver_backends_run_loop();

    return 0;
}
