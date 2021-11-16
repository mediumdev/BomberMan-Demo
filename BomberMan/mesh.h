#ifndef MESH_H
#define MESH_H

#include <QVector>
#include <QVector3D>

struct frame{
    QVector<QVector3D> verts;
};

class Mesh
{
public:
    Mesh();
    Mesh(QString path, QString filename);
    ~Mesh();
    bool load(QString path, QString filename);
    void flipLeft();
    void flipRight();
    
    void Clear();
    
    short num_frames;
    short num_tris;
    short num_verts;
    bool loaded;
    bool animated;

    QVector<float> texcoords;
    QVector<short> inds;

    QVector<frame> frames;
    
    uint texture;
};
#endif // MESH_H
