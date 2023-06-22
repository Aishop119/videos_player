#include "videos_player.h"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    videos_player w;
    w.initVideosPlayer();
    w.raise();
    w.show();
    return a.exec();
}
