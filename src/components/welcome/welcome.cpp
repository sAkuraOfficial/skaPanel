#include "welcome.h"
#include <iostream>
lot welcome_container = nullptr;

lot face_id_container = nullptr;             // 人脸登录容器
lot sign_in_or_register_container = nullptr; // 登录注册容器

lot welcome_title = nullptr;       // 欢迎标题
lot label_face_id_title = nullptr; // 登录提示标题

lot btn_face_id_sign_in = nullptr;       // 人脸登录按钮
lot btn_face_id_sign_in_label = nullptr; // 人脸登录按钮的文本

lot label_sign_title = nullptr;              // 登录注册标题
lot label_sign_title_2 = nullptr;            // 登录注册标题
lot btn_sign_in_or_register = nullptr;       // 登录注册通用按钮
lot btn_sign_in_or_register_label = nullptr; // 登录注册通用按钮的文本

lot input_username = nullptr; // 用户名输入框
lot input_password = nullptr; // 密码输入框

lot quick_login_container = nullptr; // 快速登录容器
lot btn_qq_login = nullptr;          // QQ 登录按钮
lot btn_qq_login_img = nullptr;      // QQ 登录按钮的文本
lot btn_wechat_login = nullptr;      // 微信登录按钮
lot btn_wechat_login_img = nullptr;  // 微信登录按钮的文本
lot btn_github_login = nullptr;      // 哔哩哔哩登录按钮
lot btn_github_login_img = nullptr;  // 哔哩哔哩登录按钮的文本

lot camera_container = nullptr; // 摄像头容器
lot ffmpeg_player = nullptr;    // FFmpeg 播放器对象

static lv_obj_t *part1, *part2;
static bool is_swapped = false;

#define CONTAINER_W 1400
#define CONTAINER_H 750

#define PART1_RATIO_1 400
#define PART2_RATIO_1 945

#define PART1_RATIO_2 PART2_RATIO_1
#define PART2_RATIO_2 PART1_RATIO_1

static void anim_width_cb(void *obj, int32_t value)
{
    lv_obj_set_width((lv_obj_t *)obj, value);
}

// 动画结束回调函数
void anim_ready_cb(lv_anim_t *a)
{
    static int anim_end_count = 0;
    anim_end_count++;
    if (anim_end_count == 2)
    {
        anim_end_count = 0;
        std::cout << "动画结束! 当前is_swapped状态： " << (is_swapped ? "true" : "false") << std::endl;
        if (is_swapped)
        {
            // 展开状态，开启摄像头
            lv_ffmpeg_player_set_src(ffmpeg_player, Base::instance().get_camera_stream_url().c_str()); // 设置视频源为摄像头推流 URL
            lv_ffmpeg_player_set_cmd(ffmpeg_player, LV_FFMPEG_PLAYER_CMD_START);                       // 启动播放器
        }
        else
        {
        }
    }
}

static void btn_event_cb(lv_event_t *e)
{
    // 切换比例
    int32_t w1 = is_swapped ? PART1_RATIO_1 : PART1_RATIO_2;
    int32_t w2 = is_swapped ? PART2_RATIO_1 : PART2_RATIO_2;

    if (is_swapped)
    {
        // 把camera_container放回去
        lv_ffmpeg_player_set_cmd(ffmpeg_player, LV_FFMPEG_PLAYER_CMD_STOP); // 停止播放器
        lv_anim_t anim;
        lv_anim_init(&anim);
        lv_anim_set_var(&anim, camera_container);
        lv_anim_set_exec_cb(&anim, [](void *obj, int32_t value) {
            lv_obj_set_y((lv_obj_t *)obj, value);
        });
        lv_anim_set_time(&anim, 300); // 动画时间
        lv_anim_set_values(&anim, 10, -800);
        lv_anim_set_path_cb(&anim, lv_anim_path_overshoot); // 使用缓出贝塞尔曲线
        lv_anim_start(&anim);
    }
    if (!is_swapped)
    {
        lv_obj_remove_flag(camera_container, LV_OBJ_FLAG_HIDDEN);
        lv_obj_set_style_bg_color(camera_container, lv_color_white(), 0);

        // 开启一个动画让camera_container从顶部滑入
        lv_anim_t anim;
        lv_anim_init(&anim);
        lv_anim_set_var(&anim, camera_container);
        lv_anim_set_exec_cb(&anim, [](void *obj, int32_t value) {
            lv_obj_set_y((lv_obj_t *)obj, value);
        });
        lv_anim_set_time(&anim, 300); // 动画时间
        lv_anim_set_values(&anim, -600, 10);
        lv_anim_set_path_cb(&anim, lv_anim_path_overshoot); // 使用缓出贝塞尔曲线
        lv_anim_start(&anim);
    }

    lv_anim_t a1;
    lv_anim_init(&a1);
    lv_anim_set_var(&a1, part1);
    lv_anim_set_exec_cb(&a1, anim_width_cb);
    lv_anim_set_time(&a1, 600); // 增加动画时间，让效果更明显
    lv_anim_set_values(&a1, lv_obj_get_width(part1), w1);
    lv_anim_set_path_cb(&a1, lv_anim_path_overshoot); // 使用缓出贝塞尔曲线
    lv_anim_set_ready_cb(&a1, anim_ready_cb);         // 设置动画结束回调
    lv_anim_start(&a1);                               // a1变量仅用于传递参数，因此不需要全局变量或持久化。lvgl内部会自动复制参数

    lv_anim_t a2;
    lv_anim_init(&a2);
    lv_anim_set_var(&a2, part2);
    lv_anim_set_exec_cb(&a2, anim_width_cb);
    lv_anim_set_time(&a2, 600); // 增加动画时间，让效果更明显
    lv_anim_set_values(&a2, lv_obj_get_width(part2), w2);
    lv_anim_set_path_cb(&a2, lv_anim_path_overshoot); // 使用缓出贝塞尔曲线
    lv_anim_set_ready_cb(&a2, anim_ready_cb);         // 设置动画结束回调
    lv_anim_start(&a2);

    is_swapped = !is_swapped;
}

void welcome()
{
    welcome_container = lv_obj_create(lv_scr_act());
    lv_obj_set_size(welcome_container, 1400, 800);
    lv_obj_center(welcome_container);
    lv_obj_set_style_bg_color(welcome_container, lv_color_hex(0xebeff3), 0);
    lv_obj_set_style_bg_opa(welcome_container, 200, 0);     // 背景透明
    lv_obj_set_style_border_opa(welcome_container, 200, 0); // 边框透明度

    // 设置边框
    lv_obj_set_style_border_color(welcome_container, lv_color_hex(0xd3daea), 0);
    lv_obj_set_style_border_width(welcome_container, 2, 0);

    // 设置阴影
    lv_obj_set_style_shadow_color(welcome_container, lv_color_hex(0xd5d9df), 0);
    lv_obj_set_style_shadow_width(welcome_container, 16, 0); // 阴影宽度可调
    lv_obj_set_style_shadow_ofs_x(welcome_container, 0, 0);
    lv_obj_set_style_shadow_ofs_y(welcome_container, 8, 0); // 阴影偏移可调

    // 水平布局
    lv_obj_set_flex_flow(welcome_container, LV_FLEX_FLOW_ROW);
    lv_obj_set_style_pad_column(welcome_container, 0, LV_PART_MAIN);

    { // part1
        part1 = lv_obj_create(welcome_container);

        lv_obj_set_size(part1, PART1_RATIO_1, CONTAINER_H);
        lv_obj_set_style_bg_color(part1, lv_color_hex(0xebeff3), 0);
        lv_obj_set_style_radius(part1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_clip_corner(part1, true, 0);
        mask_corner_side(part1, true);                    // 右侧遮罩
        lv_obj_clear_flag(part1, LV_OBJ_FLAG_SCROLLABLE); // 清除滚动标志(需要同时清除part1、子容器的标志才会生效)
        // lv_obj_set_style_bg_opa(part1, 128, 0);           // 背景透明
        // lv_obj_set_style_border_opa(part1, 128, 0);       // 边框透明度

        face_id_container = lv_obj_create(part1);
        lv_obj_center(face_id_container);

        lv_obj_set_flex_flow(face_id_container, LV_FLEX_FLOW_COLUMN); // 改为列布局，让元素垂直排列
        lv_obj_set_flex_align(face_id_container, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(face_id_container, LV_SIZE_CONTENT);         // 宽度自适应内容
        lv_obj_set_height(face_id_container, LV_SIZE_CONTENT);        // 高度自适应内容
        set_obj_no_bg_no_border(face_id_container);                   // 设置容器背景透明
        lv_obj_set_style_pad_row(face_id_container, 60, 0);           // 元素之间的垂直间距
        lv_obj_clear_flag(face_id_container, LV_OBJ_FLAG_SCROLLABLE); // 清除滚动标志

        welcome_title = lv_label_create(face_id_container);
        lv_label_set_text(welcome_title, "Welcome Back!");
        Base::instance().setFontToObj(welcome_title, 42);

        label_face_id_title = lv_label_create(face_id_container);
        lv_label_set_text(label_face_id_title, "使用Face ID一键登录");
        Base::instance().setFontToObj(label_face_id_title, 16);

        btn_face_id_sign_in = lv_btn_create(face_id_container);
        btn_face_id_sign_in_label = lv_label_create(btn_face_id_sign_in);
        lv_obj_center(btn_face_id_sign_in_label);
        lv_label_set_text(btn_face_id_sign_in_label, "一键登录");
        lv_obj_set_style_radius(btn_face_id_sign_in, 80, 0);
        lv_obj_set_style_pad_all(btn_face_id_sign_in, 0, 0);
        lv_obj_set_size(btn_face_id_sign_in, 200, 70);
        lv_obj_add_event_cb(btn_face_id_sign_in, btn_event_cb, LV_EVENT_CLICKED, NULL);

        camera_container = lv_obj_create(part1);
        lv_obj_set_pos(camera_container, 50, -400); // 自由定位
        lv_obj_set_size(camera_container, 800, 690);
        lv_obj_add_flag(camera_container, LV_OBJ_FLAG_HIDDEN);
        lv_obj_set_style_pad_all(camera_container, 0, 0);
        lv_obj_clear_flag(camera_container, LV_OBJ_FLAG_SCROLLABLE); // 清除滚动标志


        ffmpeg_player = lv_ffmpeg_player_create(camera_container);
        lv_obj_set_style_border_width(ffmpeg_player, 1, 0);
        lv_obj_get_style_border_color(ffmpeg_player, 0xff1234);
        lv_image_set_inner_align(ffmpeg_player, LV_IMAGE_ALIGN_CONTAIN);
    }

    { // part2

        part2 = lv_obj_create(welcome_container);
        lv_obj_set_size(part2, PART2_RATIO_1, CONTAINER_H);
        lv_obj_set_style_bg_color(part2, lv_color_hex(0xebeff3), 0);
        lv_obj_set_style_radius(part2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_clip_corner(part2, true, 0);
        mask_corner_side(part2, false); // 右侧遮罩
        lv_obj_set_style_shadow_color(part2, lv_color_hex(0xd5d9df), 0);
        lv_obj_set_style_shadow_width(part2, 16, 0); // 阴影宽度可调
        lv_obj_set_style_shadow_ofs_x(part2, -8, 0);
        lv_obj_set_style_shadow_ofs_y(part2, 0, 0); // 阴影偏移可调

        // lv_obj_set_style_bg_opa(part2, 128, 0); // 背景透明
        // lv_obj_set_style_border_opa(part2, 128, 0); // 边框透明度

        lv_obj_clear_flag(part2, LV_OBJ_FLAG_SCROLLABLE); // 清除滚动标志(需要同时清除part1、子容器的标志才会生效)

        sign_in_or_register_container = lv_obj_create(part2);
        lv_obj_center(sign_in_or_register_container);

        lv_obj_set_flex_flow(sign_in_or_register_container, LV_FLEX_FLOW_COLUMN); // 改为列布局，让元素垂直排列
        lv_obj_set_flex_align(sign_in_or_register_container, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(sign_in_or_register_container, LV_SIZE_CONTENT);         // 宽度自适应内容
        lv_obj_set_height(sign_in_or_register_container, LV_SIZE_CONTENT);        // 高度自适应内容
        set_obj_no_bg_no_border(sign_in_or_register_container);                   // 设置容器背景透明
        lv_obj_set_style_pad_row(sign_in_or_register_container, 20, 0);           // 元素之间的垂直间距
        lv_obj_clear_flag(sign_in_or_register_container, LV_OBJ_FLAG_SCROLLABLE); // 清除滚动标志

        label_sign_title = lv_label_create(sign_in_or_register_container);
        lv_label_set_text(label_sign_title, "登录账号");
        Base::instance().setFontToObj(label_sign_title, 42);

        // 快速登录容器
        quick_login_container = lv_obj_create(sign_in_or_register_container);
        lv_obj_set_flex_flow(quick_login_container, LV_FLEX_FLOW_ROW); // 水平布局
        lv_obj_set_flex_align(quick_login_container, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(quick_login_container, LV_SIZE_CONTENT);         // 宽度自适应内容
        lv_obj_set_height(quick_login_container, LV_SIZE_CONTENT);        // 高度自适应内容
        set_obj_no_bg_no_border(quick_login_container);                   // 设置容器背景透明
        lv_obj_clear_flag(quick_login_container, LV_OBJ_FLAG_SCROLLABLE); // 清除滚动标志
        lv_obj_set_style_opa(quick_login_container, 128, 0);              // 设置透明度
        lv_obj_set_style_pad_row(quick_login_container, 10, 0);           // 元素之间的水平间距
        // 快速登录按钮
        btn_qq_login = create_social_login_button(quick_login_container, "./assets/icon/qq.png");
        btn_qq_login_img = lv_obj_get_child(btn_qq_login, 0);
        btn_wechat_login = create_social_login_button(quick_login_container, "./assets/icon/wechat.png");
        btn_wechat_login_img = lv_obj_get_child(btn_wechat_login, 0);
        btn_github_login = create_social_login_button(quick_login_container, "./assets/icon/github.png");
        btn_github_login_img = lv_obj_get_child(btn_github_login, 0);

        // 登录注册标题
        label_sign_title_2 = lv_label_create(sign_in_or_register_container);
        lv_label_set_text(label_sign_title_2, "输入账号密码或使用快速登录");
        Base::instance().setFontToObj(label_sign_title_2, 16);
        lv_obj_set_style_opa(label_sign_title_2, 100, 0);

        input_username = lv_textarea_create(sign_in_or_register_container);
        lv_obj_set_size(input_username, 340, 50); // 要比part2的宽度小一些
        lv_textarea_set_placeholder_text(input_username, "username");
        Base::instance().setFontToObj(input_username, 20);
        lv_obj_set_style_radius(input_username, 8, 0);
        lv_obj_set_style_border_width(input_username, 0, 0);
        lv_obj_set_style_bg_color(input_username, lv_color_hex(0xf5f5f5), 0);
        // 设置阴影
        lv_obj_set_style_shadow_color(input_username, lv_color_hex(0xd5d9df), 0);
        lv_obj_set_style_shadow_width(input_username, 16, 0); // 阴影宽度可调
        lv_obj_set_style_shadow_ofs_x(input_username, -3, 0);
        lv_obj_set_style_shadow_ofs_y(input_username, -3, 0); // 阴影偏移可调

        input_password = lv_textarea_create(sign_in_or_register_container);
        lv_obj_set_size(input_password, 340, 50); // 要比part2的宽度小一些
        lv_textarea_set_placeholder_text(input_password, "password");
        Base::instance().setFontToObj(input_password, 20);
        lv_obj_set_style_radius(input_password, 8, 0);
        lv_obj_set_style_border_width(input_password, 0, 0);
        lv_obj_set_style_bg_color(input_password, lv_color_hex(0xf5f5f5), 0);
        lv_obj_set_style_shadow_color(input_password, lv_color_hex(0xd5d9df), 0);
        lv_obj_set_style_shadow_width(input_password, 16, 0); // 阴影宽度可调
        lv_obj_set_style_shadow_ofs_x(input_password, -3, 0);
        lv_obj_set_style_shadow_ofs_y(input_password, -3, 0); // 阴影偏移可调

        btn_sign_in_or_register = lv_btn_create(sign_in_or_register_container);
        btn_sign_in_or_register_label = lv_label_create(btn_sign_in_or_register);
        Base::instance().setFontToObj(btn_sign_in_or_register_label, 35);
        lv_obj_center(btn_sign_in_or_register_label);
        lv_label_set_text(btn_sign_in_or_register_label, "登录");
        lv_obj_set_style_radius(btn_sign_in_or_register, 80, 0);
        lv_obj_set_style_pad_all(btn_sign_in_or_register, 0, 0);
        lv_obj_set_size(btn_sign_in_or_register, 200, 55);
    }
    // 按钮
    lv_obj_t *btn = lv_btn_create(lv_scr_act());
    lv_obj_align(btn, LV_ALIGN_BOTTOM_MID, 0, -20);
    lv_obj_t *label = lv_label_create(btn);
    lv_label_set_text(label, "切换比例");
    lv_obj_center(label);
    lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_CLICKED, NULL);
}