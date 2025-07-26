#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
opencv验证测试
"""

import sys
import cv2
import numpy as np
from PyQt5.QtWidgets import (
    QApplication,
    QMainWindow,
    QVBoxLayout,
    QHBoxLayout,
    QWidget,
    QLabel,
    QPushButton,
    QMessageBox,
)
from PyQt5.QtCore import QThread, pyqtSignal, Qt
from PyQt5.QtGui import QImage, QPixmap, QFont
from picamera2 import Picamera2
import time
import os


class CameraThread(QThread):
    """摄像头线程，用于捕获和处理视频帧"""

    frame_ready = pyqtSignal(np.ndarray)
    error_occurred = pyqtSignal(str)

    def __init__(self):
        super().__init__()
        self.picam2 = None
        self.running = False
        self.face_cascade = None
        self.fps_counter = 0
        self.fps_start_time = time.time()
        self.current_fps = 0
        self.init_face_detector()

    def init_face_detector(self):
        """初始化人脸检测器"""
        try:
            # 尝试不同的级联文件路径
            current_dir = os.path.dirname(os.path.abspath(__file__))
            face_cascade_paths = [
                os.path.join(current_dir, "haarcascade_frontalface_default.xml"),
                "/usr/share/opencv4/haarcascades/haarcascade_frontalface_default.xml",
                "/usr/share/opencv/haarcascades/haarcascade_frontalface_default.xml",
            ]

            # 尝试使用cv2.data（如果可用）
            try:
                face_cascade_paths.insert(
                    0, cv2.data.haarcascades + "haarcascade_frontalface_default.xml"
                )
            except AttributeError:
                pass

            # 尝试加载人脸检测器
            for path in face_cascade_paths:
                if os.path.exists(path):
                    self.face_cascade = cv2.CascadeClassifier(path)
                    if not self.face_cascade.empty():
                        print(f"✓ 人脸检测器加载成功: {path}")
                        break

            if self.face_cascade is None or self.face_cascade.empty():
                print("警告: 无法加载人脸检测器")
                self.face_cascade = None

        except Exception as e:
            print(f"初始化人脸检测器失败: {e}")
            self.face_cascade = None

    def initialize_camera(self):
        """初始化摄像头"""
        try:
            self.picam2 = Picamera2()

            # 配置摄像头 - 使用最低画质320x240, 30fps
            config = self.picam2.create_preview_configuration(
                main={"size": (320, 240), "format": "RGB888"},
                controls={"FrameRate": 30},
            )
            self.picam2.configure(config)

            # 启动摄像头
            self.picam2.start()
            time.sleep(2)  # 等待摄像头稳定
            return True

        except Exception as e:
            self.error_occurred.emit(f"摄像头初始化失败: {str(e)}")
            return False

    def detect_faces(self, frame):
        """检测人脸"""
        if self.face_cascade is None:
            return frame

        # 转换为灰度图像用于检测
        gray = cv2.cvtColor(frame, cv2.COLOR_RGB2GRAY)

        # 检测人脸
        faces = self.face_cascade.detectMultiScale(gray, 1.1, 4)

        # 绘制人脸框
        for x, y, w, h in faces:
            # 绘制绿色人脸框
            cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)

            # 添加标签
            cv2.putText(
                frame,
                "Face",
                (x, y - 10),
                cv2.FONT_HERSHEY_SIMPLEX,
                0.6,
                (0, 255, 0),
                2,
            )

        return frame

    def calculate_fps(self):
        """计算当前FPS"""
        self.fps_counter += 1
        current_time = time.time()
        elapsed_time = current_time - self.fps_start_time

        # 每秒更新一次FPS
        if elapsed_time >= 1.0:
            self.current_fps = self.fps_counter / elapsed_time
            self.fps_counter = 0
            self.fps_start_time = current_time

    def draw_fps(self, frame):
        """在画面左上角绘制FPS"""
        fps_text = f"FPS: {self.current_fps:.1f}"

        # 绘制半透明背景
        cv2.rectangle(frame, (5, 5), (120, 35), (0, 0, 0), -1)
        cv2.rectangle(frame, (5, 5), (120, 35), (255, 255, 255), 1)

        # 绘制FPS文本
        cv2.putText(
            frame, fps_text, (10, 25), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 255, 0), 2
        )

        return frame

    def run(self):
        """线程主循环"""
        if not self.initialize_camera():
            return

        self.running = True

        try:
            while self.running:
                # 捕获帧
                frame = self.picam2.capture_array()

                if frame is not None:
                    # 计算FPS
                    self.calculate_fps()

                    # 进行人脸检测
                    processed_frame = self.detect_faces(frame)

                    # 绘制FPS显示
                    processed_frame = self.draw_fps(processed_frame)

                    # 发送处理后的帧信号
                    self.frame_ready.emit(processed_frame)

                # 控制帧率 30fps
                self.msleep(33)  # 约30fps

        except Exception as e:
            self.error_occurred.emit(f"视频捕获错误: {str(e)}")

        finally:
            self.cleanup()

    def stop(self):
        """停止线程"""
        self.running = False
        self.wait()

    def cleanup(self):
        """清理资源"""
        if self.picam2:
            try:
                self.picam2.stop()
                self.picam2.close()
            except:
                pass
            self.picam2 = None


class VideoDisplayWidget(QLabel):
    """视频显示组件"""

    def __init__(self):
        super().__init__()
        self.setMinimumSize(320, 240)
        self.setStyleSheet("border: 2px solid gray; background-color: black;")
        self.setAlignment(Qt.AlignCenter)
        self.setText("摄像头未启动")

    def update_frame(self, frame):
        """更新显示的帧"""
        try:
            height, width, channel = frame.shape

            # 转换为QImage
            bytes_per_line = channel * width
            q_image = QImage(
                frame.data, width, height, bytes_per_line, QImage.Format_BGR888
            )

            # 缩放图像
            scaled_image = q_image.scaled(
                self.size(), Qt.KeepAspectRatio, Qt.SmoothTransformation
            )

            self.setPixmap(QPixmap.fromImage(scaled_image))

        except Exception as e:
            print(f"帧更新错误: {e}")


class MainWindow(QMainWindow):
    """主窗口类"""

    def __init__(self):
        super().__init__()
        self.camera_thread = None
        self.init_ui()

    def init_ui(self):
        """初始化用户界面"""
        self.setWindowTitle("简单人脸识别")
        self.setGeometry(100, 100, 400, 350)

        # 创建中央widget
        central_widget = QWidget()
        self.setCentralWidget(central_widget)

        # 创建主布局
        main_layout = QVBoxLayout()
        central_widget.setLayout(main_layout)

        # 标题
        title_label = QLabel("简单人脸识别")
        title_label.setAlignment(Qt.AlignCenter)
        title_label.setFont(QFont("Arial", 16, QFont.Bold))
        main_layout.addWidget(title_label)

        # 视频显示区域
        self.video_widget = VideoDisplayWidget()
        main_layout.addWidget(self.video_widget)

        # 按钮布局
        button_layout = QHBoxLayout()

        # 开始/停止按钮
        self.start_button = QPushButton("开始识别")
        self.start_button.clicked.connect(self.toggle_camera)
        button_layout.addWidget(self.start_button)

        # 截图按钮
        self.screenshot_button = QPushButton("截图")
        self.screenshot_button.clicked.connect(self.take_screenshot)
        self.screenshot_button.setEnabled(False)
        button_layout.addWidget(self.screenshot_button)

        # 退出按钮
        exit_button = QPushButton("退出")
        exit_button.clicked.connect(self.close)
        button_layout.addWidget(exit_button)

        main_layout.addLayout(button_layout)

        # 状态栏
        self.statusBar().showMessage("准备就绪")

    def toggle_camera(self):
        """切换摄像头开关"""
        if self.camera_thread is None or not self.camera_thread.isRunning():
            self.start_camera()
        else:
            self.stop_camera()

    def start_camera(self):
        """启动摄像头"""
        try:
            # 创建摄像头线程
            self.camera_thread = CameraThread()

            # 连接信号
            self.camera_thread.frame_ready.connect(self.video_widget.update_frame)
            self.camera_thread.error_occurred.connect(self.handle_error)
            self.camera_thread.finished.connect(self.camera_stopped)

            # 启动线程
            self.camera_thread.start()

            # 更新UI
            self.start_button.setText("停止识别")
            self.screenshot_button.setEnabled(True)
            self.statusBar().showMessage("摄像头运行中...")

        except Exception as e:
            self.handle_error(f"启动摄像头失败: {str(e)}")

    def stop_camera(self):
        """停止摄像头"""
        if self.camera_thread and self.camera_thread.isRunning():
            self.camera_thread.stop()
            self.statusBar().showMessage("正在停止摄像头...")

    def camera_stopped(self):
        """摄像头停止回调"""
        self.start_button.setText("开始识别")
        self.screenshot_button.setEnabled(False)
        self.video_widget.setText("摄像头未启动")
        self.statusBar().showMessage("摄像头已停止")

    def take_screenshot(self):
        """截图功能"""
        if self.video_widget.pixmap():
            from datetime import datetime

            timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
            filename = f"screenshot_{timestamp}.png"

            if self.video_widget.pixmap().save(filename):
                self.statusBar().showMessage(f"截图已保存: {filename}")
                QMessageBox.information(self, "截图成功", f"截图已保存为: {filename}")
            else:
                QMessageBox.warning(self, "截图失败", "无法保存截图文件")

    def handle_error(self, error_message):
        """处理错误"""
        self.statusBar().showMessage(f"错误: {error_message}")
        QMessageBox.critical(self, "错误", error_message)
        self.stop_camera()

    def closeEvent(self, event):
        """窗口关闭事件"""
        if self.camera_thread and self.camera_thread.isRunning():
            self.camera_thread.stop()
        event.accept()


def main():
    """主函数"""
    app = QApplication(sys.argv)

    # 创建主窗口
    window = MainWindow()
    window.show()

    # 运行应用
    sys.exit(app.exec_())


if __name__ == "__main__":
    main()
