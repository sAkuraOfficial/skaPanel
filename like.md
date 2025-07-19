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
