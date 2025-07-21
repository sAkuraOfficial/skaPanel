#include "base.hpp"
#include <signal.h>
#include <unistd.h>

void Base::stop_camera_stream()
{
    Base::instance().stop_camera_stream_impl();
}

void Base::register_atexit()
{
    atexit(Base::stop_camera_stream);
}

void Base::start_camera_stream_impl()
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
               "-n",                                    // 无预览窗口
               "--width", "1080", "--height", "1080",   // 设置分辨率
               "--profile", "baseline", "--intra", "1", // 设置 I 帧间隔
               "--framerate", "30",                     // 设置帧率
               "--rotation", "180",                     // 旋转摄像头图像
               "--low-latency",                         // 低延迟模式
               "--inline",                              // 内联 pps/sps
               "--listen",                              // 监听 TCP 连接
               "--ev", "0.7",                           // 曝光值
               "--verbose", "0",                        // 日志关闭
               "--libav-format", "mpegts",              // 使用 MPEG-TS 格式
               "-o", camera_stream_url.c_str(),
               (char *)NULL); // 参数列表必须以 NULL 结尾

        // 如果 execlp 返回，说明命令执行失败
        perror("execlp failed");
        exit(EXIT_FAILURE);
    }

    // --- 这是父进程 ---
    printf("父进程: 摄像头推流子进程已启动，PID: %d\n", camera_stream_pid);
}

void Base::stop_camera_stream_impl()
{
    if (camera_stream_pid > 0)
    {
        printf("正在停止摄像头推流进程 (PID: %d)...\n", camera_stream_pid);
        kill(camera_stream_pid, SIGTERM); // 发送终止信号
        camera_stream_pid = -1;
    }
}

void Base::capture_photo_async(const std::string &filename, std::function<void(bool, const std::string &)> callback)
{
    // 创建独立线程执行拍照任务
    std::thread([this, filename, callback]() {
        printf("正在从推流中抓拍照片到: %s\n", filename.c_str());

        pid_t capture_pid = fork();

        if (capture_pid < 0)
        {
            perror("fork failed for photo capture");
            if (callback)
                callback(false, filename);
            return;
        }

        if (capture_pid == 0)
        {
            // 子进程：使用 FFmpeg 从推流中截取一帧
            execlp("ffmpeg", "ffmpeg", "-analyzeduration", "100000", // 减少网络流分析时长(要与I帧配合)
                   "-probesize", "32k",                              // 减少探测数据量
                   "-y",                                             // 覆盖输出文件
                   "-i", camera_stream_url.c_str(),                  // 输入流地址
                   "-frames:v", "1",                                 // 只截取一帧
                   "-f", "image2",                                   // 输出格式为图片
                   "-q:v", "2",                                      // 设置图片质量 (1-31, 越小质量越高)
                   "-loglevel", "quiet",                             // 减少日志输出
                   filename.c_str(),                                 // 输出文件名
                   (char *)NULL);

            perror("execlp failed for ffmpeg");
            exit(EXIT_FAILURE);
        }

        // 父进程：等待子进程完成
        int status;
        waitpid(capture_pid, &status, 0);

        bool success = (WIFEXITED(status) && WEXITSTATUS(status) == 0);
        if (success)
        {
            printf("照片抓拍成功: %s\n", filename.c_str());
        }
        else
        {
            printf("照片抓拍失败\n");
        }

        // 如果提供了回调函数，则调用它
        if (callback)
            callback(success, filename);
    }).detach(); // 分离线程，让它独立运行
}

std::string Base::get_camera_stream_url() const
{
    return camera_stream_url;
}

void Base::set_camera_stream_url(const std::string &url)
{
    camera_stream_url = url;
}

lv_font_t *Base::getFont(int size)
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

void Base::clearFonts()
{
    for (auto &kv : font_map)
    {
        lv_freetype_font_delete(kv.second);
    }
    font_map.clear();
}
