

#include <signal.h> // For kill signal constants
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> // For pid_t
#include <unistd.h>    // For fork, execlp, kill, sleep

#include "lvgl/lvgl.h"

// 添加文件资源管理器相关头文件

#include "components/welcome/welcome.h"
#include "lvgl/src/libs/ffmpeg/lv_ffmpeg.h"
#include "main.hpp"
#include "src/backend/driver_backends.h"
#include "src/backend/simulator_util.h"
#include "src/base/base.hpp"
#include <BaiduFaceID/BaiduFaceID.h>
Base &base = Base::instance();

int main()
{
    // --- LVGL 初始化 ---
    // 设置推流链接
    // printf("等待摄像头推流启动...\n");
    base.set_camera_stream_url("udp://224.1.1.1:8988");
    base.register_atexit(); // 注册退出时清理摄像头推流
    base.start_camera_stream_impl();
    sleep(2);
    printf("摄像头推流已启动，URL: %s\n", base.get_camera_stream_url().c_str());
    base.face_service = new BaiduFaceID("TOKEN", "TOKEN");
    base.user_service = new User();
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

    // lv_obj_t *player = lv_ffmpeg_player_create(lv_screen_active());
    // // 设置尺寸
    // lv_obj_set_size(player, 2160, 1440);
    // lv_ffmpeg_player_set_src(player, "./assets/calling20221009.mp4");
    // lv_ffmpeg_player_set_auto_restart(player, true);
    // lv_ffmpeg_player_set_cmd(player, LV_FFMPEG_PLAYER_CMD_START);
    // lv_obj_center(player);

    welcome();

    // --- LVGL 主循环 ---
    driver_backends_run_loop();

    return 0;
}
