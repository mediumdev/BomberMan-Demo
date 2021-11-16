#ifndef AIRFIGHTER_H
#define AIRFIGHTER_H

#include <QtGui/QMainWindow>
#include <QtOpenGL>
#include "game.h"
#include "touch.h"

class MainWindow : public QGLWidget
{
   private:
    QVector<Point> points;
    QVector<Keyboard::key> keys;
    bool press;
   protected:
        void resizeGL(int width, int height);
        void initializeGL();
        void paintGL();
   public:
        MainWindow(QWidget* parent = 0);
        
        enum ScreenOrientation {
            ScreenOrientationLockPortrait,
            ScreenOrientationLockLandscape,
            ScreenOrientationAuto
        };
        
        void setOrientation(ScreenOrientation orientation);
        void showExpanded();
        
        bool event(QEvent *e);
        void mouseMoveEvent(QMouseEvent *e);
        void mousePressEvent(QMouseEvent *e);
        void mouseReleaseEvent(QMouseEvent *e);
        
        void keyPressEvent(QKeyEvent *e);
        void keyReleaseEvent(QKeyEvent *e);
        
        Game* game;
};

#endif // AIRFIGHTER_H
