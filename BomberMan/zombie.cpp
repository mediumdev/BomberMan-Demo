#include "zombie.h"

Zombie::Zombie()
{
    addAnimation(Animation::STAY,1,31);
    addAnimation(Animation::DIE,31,51);
    addAnimation(Animation::RUN,52,75);
    addAnimation(Animation::BLOW,76,82);
    
    senemy.healch = 20;
    senemy.power = 10;
    senemy.speed = 0.7f;
    
    blow = false;
    dead = false;
    walking = false;
    walkingSide = 0;
    
    playAnim(Animation::STAY, 1.f, true);
}

Zombie::~Zombie()
{
    
}

void Zombie::clear()
{
    
}
