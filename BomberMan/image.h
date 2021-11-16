#ifndef IMAGE_H
#define IMAGE_H

#include "shader.h"
#include "camera.h"

struct imgColor
{
    float r;
    float g;
    float b;
    float a;
};

struct Img
{
    int width;
    int height;
    uint texture;
    QVector<QVector3D> verts;
    QVector<float> texc;
    QVector<short> inds;
};

struct ImgPos
{
    float x;
    float y;
};

struct ImgList
{
    QVector<ImgPos> pos;
    QVector<ImgPos> rpos;
    Img img;
};

class Image
{
private:
    
public:
    Image(QGLWidget *qglwidget);
    ~Image();
    
    int addImage(QString path, QString filename);
    int addPos(int x, int y, int index);
    void setPos(int x, int y, int imgIndex, int posIndex);
    void draw();
    void clear();
    
    QGLWidget *glwidget;
    
    QVector<ImgList> imgList;
    Shader *s_image;
};

#endif // IMAGE_H
