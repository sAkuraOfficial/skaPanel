// MySingleton.hpp
#pragma once
#include <lvgl.h>
#include <string>
#include <unordered_map>

class Base
{
  public:
    static Base &instance()
    {
        static Base _instance;
        return _instance;
    }

  private:
    Base() = default;
    ~Base() = default;
    Base(const Base &) = delete;
    Base &operator=(const Base &) = delete;

    pid_t camera_stream_pid = -1;                         // 摄像头推流子进程的 PID
    std::unordered_map<int, lv_font_t *> font_map;        // 字号到字体对象的映射
    std::string camera_stream_url = "tcp://0.0.0.0:8988"; // 摄像头推流的默认URL

    //----------------------内部工具函数----------------------
  private:
    static void stop_camera_stream()
    {
        Base::instance().stop_camera_stream_impl();
    }

    //----------------------公开函数----------------------
  public:
    void register_atexit()
    {
        atexit(Base::stop_camera_stream);
    }
    void start_camera_stream_impl()
    {
        camera_stream_pid = fork();

        if (camera_stream_pid < 0)
        {
            // Fork 失败
            perror("fork failed");
            exit(EXIT_FAILURE);
        }

        if (camera_stream_pid == 0)
        {
            // --- 这是子进程 ---
            printf("子进程: 正在启动 rpicam-vid...\n");

            // 使用 execlp 执行 rpicam-vid 命令
            // execlp 会在系统的 PATH 中查找命令
            execlp("rpicam-vid", "rpicam-vid", "-t", "0",
                   "-n",                                     // 无预览窗口
                   "--width", "1080", "--height", "1080",    // 设置分辨率
                   "--profile", "baseline", "--intra", "10", // 设置 I 帧间隔
                   "--framerate", "30",                      // 设置帧率
                   "--rotation", "180",                      // 旋转摄像头图像
                   "--low-latency",                          // 低延迟模式
                   "--inline",                               // 内联 pps/sps
                   "--listen",                               // 监听 TCP 连接
                   "--ev", "3.0",                            // 曝光值
                   "--libav-format", "mpegts",               // 使用 MPEG-TS 格式
                   "-o", camera_stream_url.c_str(),
                   (char *)NULL); // 参数列表必须以 NULL 结尾

            // 如果 execlp 返回，说明命令执行失败
            perror("execlp failed");
            exit(EXIT_FAILURE);
        }

        // --- 这是父进程 ---
        printf("父进程: 摄像头推流子进程已启动，PID: %d\n", camera_stream_pid);
    }
    void stop_camera_stream_impl()
    {
        if (camera_stream_pid > 0)
        {
            printf("正在停止摄像头推流进程 (PID: %d)...\n", camera_stream_pid);
            kill(camera_stream_pid, SIGTERM); // 发送终止信号
            camera_stream_pid = -1;
        }
    }

    std::string get_camera_stream_url() const
    {
        return camera_stream_url;
    }

    void set_camera_stream_url(const std::string &url)
    {
        camera_stream_url = url;
    }

    // 获取指定字号的字体对象，如果没有则创建
    lv_font_t *getFont(int size)
    {
        auto it = font_map.find(size);
        if (it != font_map.end())
            return it->second;

        // 判断字体有没有，没有则新建
        lv_font_t *font = lv_freetype_font_create(
            "/home/zhouzihao/fonts/SOURCEHANSANSCN-NORMAL.TTF", // 字体文件路径
            LV_FREETYPE_FONT_RENDER_MODE_BITMAP,
            size,
            LV_FREETYPE_FONT_STYLE_NORMAL
        );
        font_map[size] = font;
        return font;
    }

    // 可选：释放所有字体对象（如果需要手动释放）
    void clearFonts()
    {
        for (auto &kv : font_map)
        {
            lv_freetype_font_delete(kv.second);
        }
        font_map.clear();
    }
};
