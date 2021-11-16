#include "bomb.h"

Bomb::Bomb()
{
    addAnimation(Animation::BOMB,0.f,45.f);
    explode = false;
    sbomb.speed = 0.5f;
    sbomb.power = 1;
    
    playAnim(Animation::BOMB, sbomb.speed, false);
}

Bomb::Bomb(float _x, float _y, float _z, float _speed, int _power)
{
    addAnimation(Animation::BOMB,0.f,45.f);
    explode = false;
    sbomb.speed = _speed;
    sbomb.power = _power;
    
    playAnim(Animation::BOMB, sbomb.speed, false);
    
    setPosition(_x, _y, _z);
}

Bomb::~Bomb()
{
    clear();
}

void Bomb::update()
{
    if (frame >= end)
    {
        explode = true;
    }
}

void Bomb::clear()
{
    
}
