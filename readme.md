# skaPanel

一个基于 LVGL 的 Linux 嵌入式智能面板应用程序，集成人脸识别功能。

## 功能特性

- 基于 LVGL 9.3 的图形界面
- 支持 Linux Framebuffer 显示
- 集成百度人脸识别 API
- 摄像头视频流处理
- 触摸屏输入支持 (evdev)

## 构建要求

- CMake 3.10+
- C99/C++17 编译器
- LVGL 依赖库
- libevdev (触摸输入)
- FFmpeg

## 构建说明

```bash
mkdir build && cd build
cmake ..
make
```

## 运行

```bash
./bin/lvglsim
```

## 项目结构

- `src/` - 主要源代码
- `lvgl/` - LVGL 图形库
- `opencv_demo/` - OpenCV 人脸检测演示
- `3rd/` - 第三方依赖库

## 作者

### sAkura

- 个人博客: [https://www.sakuraofficial.site/](https://www.sakuraofficial.site/)
- 哔哩哔哩: [https://space.bilibili.com/358071887](https://space.bilibili.com/358071887)

## 许可证

本项目采用 MIT 许可证 - 详见 [LICENSE](LICENSE) 文件