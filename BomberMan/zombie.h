#ifndef ZOMBIE_H
#define ZOMBIE_H
    
#include "enemy.h" 

class Zombie : public Enemy
{
public:
    Zombie();
    virtual ~Zombie();
    
    void clear();
};

#endif // ZOMBIE_H
