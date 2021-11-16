#include "trackball.h"

#include <QDebug>
#include "math.h"

TrackBall::TrackBall(int _x, int _y, int _width, int _height)
{
    x = _x;
    y = _y;
    width = _width;
    height = _height;
    plen = 0;
    pangle = -1;
    enable = false;
}

TrackBall::~TrackBall()
{
    
}

void TrackBall::GetRotatePoint(float angle, float len, int &_x, int &_y)
{
     float rd = (90 - angle)/180*M_PI;

     _x = (int)(len*cos(rd));
     _y = (int)(len*sin(rd));
}

int TrackBall::GetLen(float x1, float y1, float x2, float y2)
{
     float xx = x1-x2;
     float yy = y1-y2;

     return (int)(sqrt(xx*xx+yy*yy));
}

int TrackBall::GetAngle(float x1, float y1, float x2, float y2)
{
     float rx, ry;
     rx = x2 - x1;
     ry = y2 - y1;
     float len = sqrt(rx*rx + ry*ry);

     if(len == 0)
         return 0;

     if(ry >= 0)
     {
         if(rx < 0)
             return 360+asin(rx/len)*180/M_PI;
         else
             return asin(rx/len)*180/M_PI;
     }

     return (int)(180 - asin(rx/len)*180/M_PI);
}

void TrackBall::setTrackPos(short touchx, short touchy)
{
    plen = GetLen(x+width/2,y+height/2,touchx,touchy);
    pangle = GetAngle(x+width/2, y+height/2, touchx, touchy);
    if (plen<=width/2){
        px = touchx;
        py = touchy;
        enable = true;
    }
    else
    {
        if (enable) 
        {
            int xx;
            int yy;
            GetRotatePoint(pangle, width/2, xx, yy);
            px = xx + x+width/2;
            py = yy + y+height/2;
        }
    }
}

void TrackBall::clear()
{
    
}
