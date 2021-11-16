#ifndef LEVEL_H
#define LEVEL_H

#include <QVector>

namespace Object
{
    enum type {
        NONE, BRIKS, CONCRETE, RESP, BLOCK, WALL, ZOMBIE, PLAYER
    };
}

struct MapStage
{
    QVector<Object::type> objects;
    QVector<Object::type> collisionobj;
};

struct Resp
{
    float x;
    float z;
    Object::type type;
};

class Level
{
public:
    Level();
    Level(QString path, QString filename);
    ~Level();
    
    Object::type getObject(int x, int y);
    void setObject(int x, int y, Object::type obj);
    Object::type getCollObject(int x, int y);
    void setCollObject(int x, int y, Object::type obj);
    
    bool load(QString path, QString filename);
    
    void clear();
    
    bool loaded;
    QVector<MapStage> stages;
    QVector<Resp> respown;
    Resp playerResp;
};

#endif // LEVEL_H
