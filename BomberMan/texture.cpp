#include "texture.h"

Texture::Texture()
{

}

Texture::Texture(QGLWidget *qglwidget)
{
    glwidget = qglwidget;
}

Texture::Texture(QString path, QString filename, QGLWidget *qglwidget)
{
    glwidget = qglwidget;
    bind(path, filename);
}

Texture::~Texture()
{
    clear();
}

void Texture::bind(QString path, QString filename)
{
    texture_path = path;
    texture_name = filename;
    QImage image = QImage(path + "/" + filename + ".png");
    sourceWidth = image.width();
    sourceHeight = image.height();
    texture = glwidget->bindTexture(image);
}

void Texture::clear()
{
    glwidget->deleteTexture(texture);
}
