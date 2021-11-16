#ifndef OBJECTS_H
#define OBJECTS_H

#include "mesh.h"
#include "shader.h"
#include "camera.h"

struct Param
{
    QMatrix4x4 orient;
    int frame;
    QVector4D color;
};

struct Meshes
{
    Mesh *mesh;
    bool oneframe;
    QVector<Param> params;
};

class Objects
{
private:
    int lastframe;
public:
    Objects();
    Objects(QGLWidget *qglwidget);
    ~Objects();
    
    int addMesh(Mesh *mesh); 
    void addParam(QMatrix4x4 orient, int frame, QVector4D color, int index); 
    void draw(Camera *camera);
    
    void clear();
    
    QVector<Meshes> meshes;
    
    Shader *s_textured;
};

#endif // OBJECTS_H
