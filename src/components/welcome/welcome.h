#pragma once
#include "base/base.hpp"
extern lot welcome_container;

extern lot face_id_container;             // 人脸登录容器
extern lot sign_in_or_register_container; // 登录注册容器

extern lot welcome_title;       // 欢迎标题
extern lot label_face_id_title; // 登录提示标题

extern lot btn_face_id_sign_in;       // 人脸登录按钮
extern lot btn_face_id_sign_in_label; // 人脸登录按钮的文本

extern lot label_sign_title;              // 登录注册标题
extern lot label_sign_title_2;            // 登录注册标题
extern lot btn_sign_in_or_register;       // 登录注册通用按钮
extern lot btn_sign_in_or_register_label; // 登录注册通用按钮的文本

extern lot input_username; // 用户名输入框
extern lot input_password; // 密码输入框

extern lot quick_login_container; // 快速登录容器
extern lot btn_qq_login;          // QQ 登录按钮
extern lot btn_qq_login_img;      // QQ 登录按钮的文本
extern lot btn_wechat_login;      // 微信登录按钮
extern lot btn_wechat_login_img;  // 微信登录按钮的文本
extern lot btn_github_login;      // 哔哩哔哩登录按钮
extern lot btn_github_login_img;  // 哔哩哔哩登录

extern lot camera_container; // 摄像头容器
extern lot ffmpeg_player;    // FFmpeg 播放器对象

// extern lot face_id_animation_container; // 人脸识别动画容器
extern lot face_id_animation; // 人脸识别动画对象

extern lot btn_face_id_try_again; // 人脸识别失败重试按钮
extern lot btn_face_id_try_again_label; // 人脸识别失败重试按钮的文本

extern lot label_say_hello_to_user; // 欢迎用户的标签


void welcome();