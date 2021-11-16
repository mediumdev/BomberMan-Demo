#include "touch.h"

Touch::Touch()
{
    x = 0;
    y = 0;
    width = 0;
    height = 0;
}

Touch::~Touch()
{
    clear();
}

void Touch::setObjParams(int objx, int objy, int objwidth, int objheight)
{
    x = objx;
    y = objy;
    width = objwidth;
    height = objheight;
}

void Touch::update(QVector<Point> &points)
{
    touchOver=false;
    touchOut=false;
    touchDown=false;
    touchUp=false;
    touchMove=false;
    touchLocalX=0;
    touchLocalY=0;
    touchX=0;
    touchY=0;
    
    int numpointsover=0;
    
    if (points.count()>0)
    {
        for (int i = 0; i < points.count(); i++)
        {
            touchX=points[i].x;
            touchY=points[i].y;
            if ((points[i].x>=x) && (points[i].x<=x+width) && (points[i].y>=y) && (points[i].y<=y+height))
            {
                touchLocalX=points[i].x-x;
                touchLocalY=points[i].y-y;
                
                numpointsover++;
                if ((points[i].state == Qt::TouchPointMoved) || (points[i].mouseState == 1))
                { 
                    touchMove=true;
                }
                if ((points[i].state == Qt::TouchPointPressed) || (points[i].mouseState == 2))
                {
                    touchDown=true;
                }
                if ((points[i].state == Qt::TouchPointReleased) || (points[i].mouseState == 3)) 
                {
                    touchUp=true;
                }
            }
        }
        if (numpointsover>0) touchOver=true;
        else touchOut=true;
    }
}

void Touch::clear()
{
    
}
