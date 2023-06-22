#pragma once

#include <QtWidgets/QMainWindow>
#include <qscreen.h>
#include <QtAV/VideoOutput.h>
#include <QtAV/AVPlayer.h>
#include <QtAV/VideoCapture.h>
#include <QtAV/VideoFrame.h>
#include <QtAVWidgets/WidgetRenderer.h>
#include <QGridLayout.h>
#include <qpushbutton.h>
#include <qdebug.h>
#include <QDateTime >

#include <math.h>

#include "source.h"
#include "ui_videos_player.h"

class videos_player : public QWidget
{
    Q_OBJECT

public:
    videos_player(QWidget *parent = nullptr);
    ~videos_player();
    void initVideosPlayer();
    void resetButton(QPushButton* but, const QString path, uint16_t x, uint16_t y);
    int calculateAvailableHeight();
private:
    Ui::videos_playerClass ui;
    uint32_t desktop_width_;
    uint32_t desktop_height_;
    uint32_t video_width_;
    uint32_t video_height_;



    QGridLayout* players_layout_;
    uint16_t rows;
    uint16_t columns;


    QtAV::VideoOutput* video_outputs_[VIDEO_COUNT];
    QtAV::AVPlayer* video_players_[VIDEO_COUNT];

    QPushButton* video_size_buttons_[VIDEO_COUNT];
    QPushButton* video_screenshort_buttons_[VIDEO_COUNT];

    std::string video_paths[VIDEO_COUNT] = {
            "D:/C++_workspace/vs_2022/XPlay2/test_1280x720.mp4",
            "D:/C++_workspace/vs_2022/XPlay2/test_1280x720.mp4",
            "D:/C++_workspace/vs_2022/XPlay2/test_1280x720.mp4",
            "D:/C++_workspace/vs_2022/XPlay2/test_1280x720.mp4",
            "D:/C++_workspace/vs_2022/XPlay2/test_1280x720.mp4",
            "D:/C++_workspace/vs_2022/XPlay2/test_1280x720.mp4",
            "D:/C++_workspace/vs_2022/XPlay2/test_1280x720.mp4",
            "D:/C++_workspace/vs_2022/XPlay2/test_1280x720.mp4",
            "D:/C++_workspace/vs_2022/XPlay2/test_1280x720.mp4"
            
    };

private slots:
    void  onButtonSizeClicked();
    void  onButtonScreenshotClicked();
    void onCaptureSaved(const QString& path);
    
};
