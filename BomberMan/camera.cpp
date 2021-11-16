#include "camera.h"

Camera::Camera(QGLWidget *qglwidget)
{
    glwidget = qglwidget;
    
    vx=0;
    vy=0;
    x=0.f;
    y=0.f;
    z=0.f;
    width=glwidget->width();
    height=glwidget->height();
    fullscreen=true;
    
    r = 0.f;
    g = 0.f;
    b = 0.f;
    a = 1.f;
    
    p_angle = 0.f; p_aspect = 0.f; p_cnear = 0.f; p_cfar = 0.f;
    t_cx = 0.f; t_cy = 0.f; t_cz = 0.f;
    r_angle = 0.f; r_cx = 0.f; r_cy = 0.f; r_cz = 0.f;
}

Camera::~Camera()
{
    clear();
}

void Camera::rotate(qreal angle, qreal cx, qreal cy, qreal cz)
{
    projection.rotate(angle, cx, cy, cz);
    r_angle = angle;
    r_cx = cx;
    r_cy = cy;
    r_cz = cz;
}

void Camera::translate(qreal cx, qreal cy, qreal cz)
{
    projection.translate(cx, cy, cz);
    t_cx = cx;
    t_cy = cy;
    t_cz = cz;
}

void Camera::goTo(qreal cx, qreal cy, qreal cz)
{
    x = cx;
    y = cy;
    z = cz;
    projection.setToIdentity();
    projection.perspective(p_angle, p_aspect, p_cnear, p_cfar);
    projection.rotate(r_angle, r_cx, r_cy, r_cz);
    projection.translate(x, y, z);
}

void Camera::viewport(GLint cx, GLint cy)
{
    vx=cx;
    vy=cy;
}

void Camera::viewport(GLint cx, GLint cy, GLsizei cwidth, GLsizei cheight)
{
    vx=cx;
    vy=cy;
    width=cwidth;
    height=cheight;
    fullscreen = false;
}

void Camera::perspective(qreal angle, qreal aspect, qreal cnear, qreal cfar)
{
    projection.perspective(angle, aspect, cnear, cfar);
    p_angle = angle;
    p_aspect = aspect;
    p_cnear = cnear; 
    p_cfar = cfar;
}

void Camera::clearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
    r=red;
    g=green;
    b=blue;
    a=alpha;
}

void Camera::begin()
{
    if (fullscreen)
    {
        width=glwidget->width();
        height=glwidget->height();
    }
    
    glViewport(0, 0, width, height);
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Camera::touchUpdate(QVector<Point> &touchpoints)
{
    points.clear();
    points = touchpoints;
    
    Touch touch;
    touch.setObjParams(vx, vy, width, height);
    touch.update(points);
    touchOver=touch.touchOver;
    touchOut=touch.touchOut;
    touchDown=touch.touchDown;
    touchUp=touch.touchUp;
    touchMove=touch.touchMove;
    touchX=touch.touchX;
    touchY=touch.touchY;
    touchLocalX=touch.touchLocalX;
    touchLocalY=touch.touchLocalY;
}

void Camera::clear()
{

}
