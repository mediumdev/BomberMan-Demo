#ifndef CAMERA_H
#define CAMERA_H

#include <QGLWidget>
#include <QMatrix4x4>
#include "touch.h"

class Camera
{
private:
    GLclampf r;
    GLclampf g;
    GLclampf b;
    GLclampf a;
    
    bool fullscreen;
    
    QVector<Point> points;
    
    qreal p_angle; qreal p_aspect; qreal p_cnear; qreal p_cfar;
    qreal t_cx; qreal t_cy; qreal t_cz;
    qreal r_angle; qreal r_cx; qreal r_cy; qreal r_cz;
public:
    Camera(QGLWidget *qglwidget);
    ~Camera();

    void rotate(qreal angle, qreal cx, qreal cy, qreal cz);
    void translate(qreal cx, qreal cy, qreal cz);
    void goTo(qreal cx, qreal cy, qreal cz);
    void viewport(GLint cx, GLint cy);
    void viewport(GLint cx, GLint cy, GLsizei cwidth, GLsizei cheight);
    void perspective(qreal angle, qreal aspect, qreal cnear, qreal cfar);
    void clearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
    void begin();
    
    void touchUpdate(QVector<Point> &touchpoints);
    
    void clear();

    QGLWidget *glwidget;
    
    int vx;
    int vy;
    int width;
    int height;
    
    float x;
    float y;
    float z;
    
    int touchX;
    int touchY;
    int touchLocalX;
    int touchLocalY;
    bool touchOver;
    bool touchOut;
    bool touchDown;
    bool touchUp;
    bool touchMove;
    QMatrix4x4 projection;
};

#endif // CAMERA_H
