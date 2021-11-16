#ifndef TOUCH_H
#define TOUCH_H

#include <QVector>
#include <QTouchEvent>

struct Point
{
    int x;
    int y;
    Qt::TouchPointStates state;
    int mouseState;
};

class Touch
{
private:
    int x;
    int y;
    int width;
    int height;
public:
    Touch();
    ~Touch();
    
    void setObjParams(int objx, int objy, int objwidth, int objheight);
    void update(QVector<Point> &points);
    
    void clear();
    
    int touchX;
    int touchY;
    int touchLocalX;
    int touchLocalY;
    bool touchOver;
    bool touchOut;
    bool touchDown;
    bool touchUp;
    bool touchMove;
};

#endif // TOUCH_H
