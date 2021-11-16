#ifndef BOMB_H
#define BOMB_H

#include "model.h"

struct sBomb
{
    float speed;
    int power;
};

class Bomb : public Model
{
public:
    Bomb();
    Bomb(float _x, float _y, float _z, float _speed, int _power);
    virtual ~Bomb();
    
    void update();
    
    void clear();
    
    bool explode;
    sBomb sbomb;
};

#endif // BOMB_H
