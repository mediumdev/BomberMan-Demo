#ifndef MODEL_H
#define MODEL_H

#include <QVector4D>
#include "mesh.h"
#include "level.h"

namespace Side
{
    enum en {
       UP, DOWN, LEFT, RIGHT
    };
}

namespace Animation
{
    enum Type {
        NONE, STAY, RUN, DIE, HIT, BOMB, EXPLOSION, BLOW
    };
}

struct AnimKeys
{
    Animation::Type type;
    float start;
    float end;
};

class Model
{
protected:
    Animation::Type animType;
    
    bool chekCollision(Level *level, int xx, int zz, Object::type _type);
public:
    Model();
    ~Model();
    
    void updateCollision(Level *level);
    void setPosition(float _x, float _y, float _z);
    void setAngle(int _angle);
    void addAnimation(Animation::Type _type, float _start, float _end);
    void playAnim(Animation::Type type, float _speed, bool _loop);
    void updateAnim();
    void stopAnim();
    void clear();
    
    QVector<AnimKeys> anim;
    float frame;
    bool animate;
    
    bool cUp;
    bool cDown;
    bool cLeft;
    bool cRight;
    bool cPlayer;
    
    float start;
    float end;
    float speed;
    bool loop;
    
    float x;
    float y;
    float z;
    int angle;
    
    QVector4D color;
    
    Side::en side;
};

#endif // MODEL_H
