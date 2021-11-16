#include "image.h"

Image::Image(QGLWidget *qglwidget)
{   
    glwidget = qglwidget;
    s_image = new Shader(":/shaders", "image", glwidget);
}

int Image::addImage(QString path, QString filename)
{
    QImage image = QImage(path + "/" + filename);
    ImgList im;
    im.img.texture = glwidget->bindTexture(image);
    im.img.width = image.width();
    im.img.height = image.height();
    
    im.img.inds.append(0);
    im.img.inds.append(1);
    im.img.inds.append(2);
    im.img.inds.append(1);
    im.img.inds.append(2);
    im.img.inds.append(3);
    
    im.img.texc.append(0.f);
    im.img.texc.append(1.f);
    im.img.texc.append(1.f);
    im.img.texc.append(1.f);
    im.img.texc.append(0.f);
    im.img.texc.append(0.f);
    im.img.texc.append(1.f);
    im.img.texc.append(0.f);
    
    float imgwidth = (float)(2.f/glwidget->width()*(float)image.width());
    float imgheight = (float)(2.f/glwidget->height()*(float)image.height());
    
    im.img.verts.append(QVector3D(0.f,0.f,0.f));
    im.img.verts.append(QVector3D(imgwidth,0.f,0.f));
    im.img.verts.append(QVector3D(0.f,0.f-imgheight,0.f));
    im.img.verts.append(QVector3D(imgwidth,0.f-imgheight,0.f));
    
    imgList.append(im);
    
    return imgList.count()-1;
}

int Image::addPos(int x, int y, int index)
{
    ImgPos pos;
    
    pos.x = x;
    pos.y = y;
    imgList[index].rpos.append(pos);
    
    float xx = (float)(2.f/glwidget->width()*x-1.f);
    float yy = (float)(1.f-(2.f/glwidget->height()*y));
    
    pos.x = xx;
    pos.y = yy;
    imgList[index].pos.append(pos);
    
    return imgList[index].pos.count()-1;
}

void Image::setPos(int x, int y, int imgIndex, int posIndex)
{
    imgList[imgIndex].pos[posIndex].x = x;
    imgList[imgIndex].pos[posIndex].y = y;
    
    float xx = (float)(2.f/glwidget->width()*x-1.f);
    float yy = (float)(1.f-(2.f/glwidget->height()*y));
    
    imgList[imgIndex].pos[posIndex].x = xx;
    imgList[imgIndex].pos[posIndex].y = yy;
}

void Image::draw()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    QMatrix4x4 orient;
    
    s_image->bind();
    for (int i = 0; i < imgList.count(); i++)
    {
        s_image->setUniform("tex", imgList[i].img.texture);
        s_image->setAttribute("texCoord", imgList[i].img.texc.data(), 2);
        s_image->setAttribute("vertex", imgList[i].img.verts.data());
        
        for (int j = 0; j < imgList[i].pos.count(); j++)
        {
            orient.setToIdentity();
            orient.translate(imgList[i].pos[j].x, imgList[i].pos[j].y, 0);
            s_image->setUniform("matrix", orient);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, imgList[i].img.inds.data());
        }
    }
    s_image->disableAttribute("vertex");
    s_image->disableAttribute("texCoord");
    s_image->release();
    
    glDisable(GL_BLEND);
}

Image::~Image()
{
    clear();
}

void Image::clear()
{
    
}
