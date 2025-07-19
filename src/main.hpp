#pragma once

#include <lvgl.h>
#define lot lv_obj_t *
#include <string>
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
