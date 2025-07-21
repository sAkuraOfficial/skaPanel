#include "welcome.h"

lot welcome_container = nullptr;

lot welcome_title = nullptr;       // 欢迎标题
lot label_sign_in_title = nullptr; // 登录提示标题

lot btn_sign_in = nullptr;       // 登录按钮
lot btn_sign_in_label = nullptr; // 登录按钮的文本

lot btn_register = nullptr;       // 注册按钮
lot btn_register_label = nullptr; // 注册按钮的文本

lot input_username = nullptr; // 用户名输入框
lot input_password = nullptr; // 密码输入框

lot btn_qq_login = nullptr;       // QQ 登录按钮
lot btn_qq_login_label = nullptr; // QQ 登录按钮的文本

lot btn_wechat_login = nullptr;       // 微信登录按钮
lot btn_wechat_login_label = nullptr; // 微信登录按钮的文本

lot btn_bilibili_login = nullptr;       // 哔哩哔哩登录按钮
lot btn_bilibili_login_label = nullptr; // 哔哩哔哩登录按钮的文本

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

static void btn_event_cb(lv_event_t *e)
{
    // 切换比例
    int32_t w1 = is_swapped ? PART1_RATIO_1 : PART1_RATIO_2;
    int32_t w2 = is_swapped ? PART2_RATIO_1 : PART2_RATIO_2;

    lv_anim_t a1;
    lv_anim_init(&a1);
    lv_anim_set_var(&a1, part1);
    lv_anim_set_exec_cb(&a1, anim_width_cb);
    lv_anim_set_time(&a1, 800);
    lv_anim_set_values(&a1, lv_obj_get_width(part1), w1);
    lv_anim_start(&a1);

    lv_anim_t a2;
    lv_anim_init(&a2);
    lv_anim_set_var(&a2, part2);
    lv_anim_set_exec_cb(&a2, anim_width_cb);
    lv_anim_set_time(&a2, 800);
    lv_anim_set_values(&a2, lv_obj_get_width(part2), w2);
    lv_anim_start(&a2);

    is_swapped = !is_swapped;
}

void welcome()
{
    welcome_container = lv_obj_create(lv_scr_act());
    lv_obj_set_size(welcome_container, 1400, 800);
    lv_obj_center(welcome_container);
    lv_obj_set_style_bg_color(welcome_container, lv_color_hex(0xebeff3), 0);

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

    // part1
    part1 = lv_obj_create(welcome_container);
    lv_obj_set_size(part1, PART1_RATIO_1, CONTAINER_H);
    lv_obj_set_style_bg_color(part1, lv_color_hex(0xebeff3), 0);
    lv_obj_set_style_radius(part1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(part1, true, 0);
    mask_corner_side(part1, true); // 左侧遮罩
    // lv_obj_t *mask_rect = lv_obj_create(part1);
    // lv_obj_set_size(mask_rect, lv_pct(100), lv_pct(100)); // 尺寸与父对象 my_obj 相同
    // lv_obj_remove_style_all(mask_rect);
    // lv_obj_set_style_border_width(mask_rect, 15, 0);
    // lv_obj_set_style_border_color(mask_rect, lv_obj_get_style_bg_color(part1, 0), 0);
    // lv_obj_set_style_border_side(mask_rect, LV_BORDER_SIDE_LEFT, 0); // 只显示左边框

    // part2
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

    // 按钮
    lv_obj_t *btn = lv_btn_create(lv_scr_act());
    lv_obj_align(btn, LV_ALIGN_BOTTOM_MID, 0, -20);
    lv_obj_t *label = lv_label_create(btn);
    lv_label_set_text(label, "切换比例");
    lv_obj_center(label);
    lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_CLICKED, NULL);
}