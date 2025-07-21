## 文件资源管理器

```c

// 文件资源管理器事件回调
static void file_explorer_event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj       = lv_event_get_target_obj(e);

    if(code == LV_EVENT_VALUE_CHANGED) {
        const char * cur_path = lv_file_explorer_get_current_path(obj);
        const char * sel_fn   = lv_file_explorer_get_selected_file_name(obj);
        LV_LOG_USER("%s%s", cur_path, sel_fn);
    }
}

    // 添加文件资源管理器窗口
    lv_obj_t * file_explorer_window =
        create_draggable_window("File Explorer", screen_width / 2, screen_height - 80, screen_width / 2 + 15, 15);
    lv_obj_t * file_explorer = lv_file_explorer_create(file_explorer_window);
    lv_obj_set_size(file_explorer, screen_width / 2 - 4, screen_height - 80 - 35);
    lv_obj_set_pos(file_explorer, 2, 32);
    lv_file_explorer_set_sort(file_explorer, LV_EXPLORER_SORT_KIND);
    lv_file_explorer_open_dir(file_explorer, "A:/"); // 挂载的文件系统路径
    lv_obj_add_event_cb(file_explorer, file_explorer_event_handler, LV_EVENT_ALL, NULL);
```

## 推流命令

```bash
rpicam-vid -t 0 -n --width 1296 --height 972 --inline --listen --libav-format mpegts -o tcp://0.0.0.0:8988
```

```bash
curl -X POST 'https://facebody.cn-shanghai.aliyuncs.com/' \
  -H 'Content-Type: application/x-www-form-urlencoded' \
  -d 'Action=AddFaceEntity' \
  -d 'Version=2019-12-30' \
  -d 'DbName=face' \
  -d 'EntityId=202235010732' \
  -d 'RegionId=cn-shanghai' \
  -d 'AccessKeyId=LTAI5tBwu1V71psa7jTZJ238' \
  -d 'SignatureNonce=unique-random-string' \
  -d 'Timestamp=2025-07-20T15:34:16Z' \
  -d 'SignatureMethod=HMAC-SHA1' \
  -d 'SignatureVersion=1.0' \
  -d 'Signature=your-calculated-signature'

```

```cpp



lv_obj_t *img = nullptr;
// 基础容器
lot info_contaner = nullptr;
lot info_tableView = nullptr;

// 页
lot page1 = nullptr;
lot page2 = nullptr;

// 组件
std::string face_name = "...";
lot button_check_face = nullptr;
lot button_check_face_label = nullptr;
lot label_name_show = nullptr;
lot img_test = nullptr;
```

```cpp
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
        lv_ffmpeg_player_set_src(img, base.get_camera_stream_url().c_str()); // 设置视频源为摄像头推流 URL
        lv_ffmpeg_player_set_cmd(img, LV_FFMPEG_PLAYER_CMD_START);
        printf("摄像头播放器已恢复播放\n");
    }
}


 lv_obj_t *tv = lv_tabview_create(lv_screen_active()); // 创建一个标签视图
    lv_obj_t *t1 = lv_tabview_add_tab(tv, "人脸录入");
    lv_obj_t *t2 = lv_tabview_add_tab(tv, "Analytics");
    lv_obj_t *t3 = lv_tabview_add_tab(tv, "Shop");
    // 设置背景颜色204, 233, 247
    lv_color_t color_temp = {247,233,204};
    lv_obj_set_style_bg_color(tv, color_temp, 0);
    
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
                    // 立即更新UI显示正在拍照
                    face_name = "正在拍照...";
                    lv_label_set_text_fmt(label_name_show, "识别结果：%s", face_name.c_str());

                    // 使用异步拍照函数，不阻塞UI线程
                    base.capture_photo_async("/home/zhouzihao/cppProject/skaPanel/asd.png", [](bool success, const std::string &filename) {
                        // 拍照完成的回调函数
                        if (success)
                        {
                            face_name = "拍照成功";
                        }
                        else
                        {
                            face_name = "拍照失败";
                        }

                        // 使用LVGL的异步更新机制
                        lv_async_call(
                            [](void *) {
                                base.face_service->login(
                                    loadImageAsBytes("/home/zhouzihao/cppProject/skaPanel/asd.png"),
                                    [](const std::string &userId) {
                                        face_name = userId;
                                        lv_label_set_text_fmt(label_name_show, "识别结果：%s", face_name.c_str());
                                    },
                                    [](const std::string &errorStr) {
                                        face_name = "识别失败: " + errorStr;
                                        lv_label_set_text_fmt(label_name_show, "识别结果：%s", face_name.c_str());
                                    }
                                );
                            },
                            nullptr
                        );
                    });
                }
            },
            LV_EVENT_ALL,
            NULL
        );
        lv_obj_center(button_check_face_label);

        img_test = lv_img_create(page1);
        lv_img_set_src(img_test, "/home/zhouzihao/cppProject/skaPanel/asd.png");
    }

```
