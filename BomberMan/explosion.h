#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "model.h"

struct sExpl
{
    float speed;
    int power;
};

struct sExplFire
{
    int x;
    int z;
};

class Explosion : public Model
{
public:
    Explosion();
    Explosion(float _x, float _y, float _z, float _speed, int _power, Level *level);
    virtual ~Explosion();
    
    void update();
    int checkDamage(Model *_model);
    
    void clear();
    
    sExpl sexpl;
    bool endExpl;
    QVector<sExplFire> explfire;
};

#endif // EXPLOSION_H
