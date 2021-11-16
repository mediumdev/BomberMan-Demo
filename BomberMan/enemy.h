#ifndef ENEMY_H
#define ENEMY_H

#include "model.h"

struct sEnemy
{
    float speed;
    int healch;
    int power;
};

class Enemy : public Model
{
public:
    Enemy();
    virtual ~Enemy();
    
    bool collModel(Model *_model);
    void update();
    void walk();
    
    void clear();
    
    bool dead;
    bool walking;
    bool blow;
    int walkingSide;
    
    sEnemy senemy;
};

#endif // ENEMY_H
