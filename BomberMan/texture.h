#ifndef TEXTURE_H
#define TEXTURE_H

#include <QString>
#include <QtOpenGL>

class Texture
{
public:
    Texture();
    Texture(QGLWidget *qglwidget);
    Texture(QString path, QString filename, QGLWidget *qglwidget);
    ~Texture();
    
    void bind(QString path, QString filename);
    
    void clear();
    
    QGLWidget *glwidget;
    
    int sourceWidth;
    int sourceHeight;
    
    QString texture_path;
    QString texture_name;
    uint texture;
};

#endif // TEXTURE_H
