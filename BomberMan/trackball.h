#ifndef TRACKBALL_H
#define TRACKBALL_H

class TrackBall
{
private:
    void GetRotatePoint(float angle, float len, int &_x, int &_y);
    int GetAngle(float x1, float y1, float x2, float y2);
    int GetLen(float x1, float y1, float x2, float y2);
public:
    TrackBall(int _x, int _y, int _width, int _height);
    ~TrackBall();
    
    void setTrackPos(short touchx, short touchy);
    
    void clear();
    
    int x;
    int y;
    int width;
    int height;
    int px;
    int py;
    int pangle;
    int plen;
    
    bool enable;
};

#endif // TRACKBALL_H
