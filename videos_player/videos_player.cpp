#include "videos_player.h"


void videos_player::initVideosPlayer() {

    for (int i = 0; i < VIDEO_COUNT; ++i) {
        video_outputs_[i] = new QtAV::VideoOutput(this); 
        players_layout_->addWidget(video_outputs_[i]->widget(), i / columns, i % columns);
        
        video_outputs_[i]->widget()->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        QString button_name = "videosizeshotbutton_" + QString::fromStdString(std::to_string(i));
        
        video_size_buttons_[i] = new QPushButton( video_outputs_[i]->widget());
        video_size_buttons_[i]->setObjectName(button_name);
        resetButton(video_size_buttons_[i],"res/fullScreenEnter.png",660,360);
        QObject::connect(video_size_buttons_[i], &QPushButton::clicked, this, &videos_player::onButtonSizeClicked);

        video_screenshort_buttons_[i] = new QPushButton(video_outputs_[i]->widget());
        resetButton(video_screenshort_buttons_[i], "res/screenshot.png", 600, 360);
        button_name = "videoscreenshotbutton_" + QString::fromStdString(std::to_string(i));
        video_screenshort_buttons_[i]->setObjectName(button_name);
        QObject::connect(video_screenshort_buttons_[i], &QPushButton::clicked, this, &videos_player::onButtonScreenshotClicked);

        video_players_[i] = new QtAV::AVPlayer(this);
        video_players_[i]->addVideoRenderer(video_outputs_[i]);

        video_players_[i]->setFile(QString::fromStdString(video_paths[i]));
        video_players_[i]->audio()->setBackends(QStringList() << "null");  //静音
        video_players_[i]->play();
        video_players_[i]->videoCapture()->setAsync();
        //connect(video_players_[i]->videoCapture(), SIGNAL(imageCaptured(QImage)), SLOT(updatePreview(QImage)));
        connect(video_players_[i]->videoCapture(), SIGNAL(saved(QString)), SLOT(onCaptureSaved(QString)));
        //connect(video_players_[i]->videoCapture(), SIGNAL(failed()), SLOT(onCaptureError()));
  

    }
    video_height_ = video_outputs_[0]->widget()->height();
    video_width_ = video_outputs_[0]->widget()->width();

}

videos_player::videos_player(QWidget *parent)
    : QWidget(parent)
{
    //ui.setupUi();
    QScreen* screen = qApp->primaryScreen();
    desktop_width_ = screen->size().width();
    QRect availableGeometry = screen->availableGeometry();
    desktop_height_ = availableGeometry.height();
    this->resize(desktop_width_, desktop_height_);
    players_layout_ = new QGridLayout(this);
    players_layout_->setContentsMargins(1, 1, 1, 1);

    rows = sqrt(VIDEO_COUNT);
    columns = sqrt(VIDEO_COUNT);
}

videos_player::~videos_player()
{}


void  videos_player::onButtonScreenshotClicked() {
    QPushButton* button_screenshot = qobject_cast<QPushButton*>(sender());
    QString button_name = button_screenshot->objectName();
    int i = button_name.back().toLatin1() - '0';
   
    video_players_[i]->videoCapture()->setCaptureDir("res/screenshot");
    video_players_[i]->videoCapture()->capture();
    
}

void videos_player::onCaptureSaved(const QString& path) {
    setWindowTitle(tr("saved to: ") + path);
}


void videos_player::onButtonSizeClicked()
{
    QPushButton* button_size = qobject_cast<QPushButton*>(sender());
    QString button_size_name = button_size->objectName();
    QString button_screenshot_name = "videoscreenshotbutton_" + button_size_name.back();
    //QString str = button_size_name.back();
    qDebug() << button_screenshot_name;
    //qDebug() << str;
    if (button_size)
    {
        QWidget* widget = button_size->parentWidget();
        QPushButton* button_screenshot = widget->findChild<QPushButton*>(button_screenshot_name);
        
        if (widget)
        {
            if (widget->width() <= desktop_width_ / 2)
            {
                // 全屏
                widget->setGeometry(0, 0, desktop_width_, desktop_height_);
                widget->showFullScreen();
                widget->raise();
                resetButton(button_size, "res/fullScreenExit.png", desktop_width_ - 100, desktop_height_ - 100);
                resetButton(button_screenshot, "res/screenshot.png", desktop_width_ - 170, desktop_height_ - 100);
            }
            else
            {
                // 退出全屏
                widget->showNormal();
                this->resize(desktop_width_ - 1, desktop_height_);
                this->resize(desktop_width_, desktop_height_);
                resetButton(button_size, "res/fullScreenEnter.png", widget->width() - 80, widget->height() - 70);
                resetButton(button_screenshot, "res/screenshot.png", widget->width() - 140, widget->height() - 70);
            }
            
        }
    }
}

void videos_player::resetButton(QPushButton* but,const QString path,uint16_t x, uint16_t y) {

    QIcon icon(path);
    but->resize(40, 40);
    but->setIcon(icon);
    but->setStyleSheet("QPushButton { background: transparent; }");
    but->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    QSize iconSize = icon.actualSize(but->size());
    but->setIconSize(iconSize);
    but->move(x, y);
    
}


