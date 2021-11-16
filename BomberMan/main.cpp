#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow mainWindow;
#if defined(Q_OS_SYMBIAN) || defined(Q_WS_SIMULATOR)
    mainWindow.showFullScreen();
#else
    mainWindow.resize(640,360);
    mainWindow.showFullScreen();
#endif    
    return app.exec();
}
