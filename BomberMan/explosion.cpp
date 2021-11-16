#include "explosion.h"

Explosion::Explosion()
{
    addAnimation(Animation::EXPLOSION,0.f,10.f);
    
    sexpl.speed = 1.f;
    sexpl.power = 1;
    endExpl = false;
    
    playAnim(Animation::EXPLOSION, sexpl.speed, false);
}

Explosion::Explosion(float _x, float _y, float _z, float _speed, int _power, Level *level)
{
    addAnimation(Animation::EXPLOSION,0.f,10.f);
    
    sexpl.speed = _speed;
    sexpl.power = _power;
    endExpl = false;
    
    playAnim(Animation::EXPLOSION, sexpl.speed, false);
    
    setPosition(_x, _y, _z);
    
    int en1 = 0; int en2 = 0; int en3 = 0; int en4 = 0; 
    en1 = (int)x/10+sexpl.power+1;
    en2 = (int)x/10-sexpl.power-1;
    en3 = (int)z/10+sexpl.power+1;
    en4 = (int)z/10-sexpl.power-1;
    
    if (en1 >= level->stages[0].objects.count()) en1 = level->stages[0].objects.count()-1;
    if (en2 < 0) en2 = 0;
    if (en3 >= level->stages.count()) en3 = level->stages.count()-1;
    if (en4 < 0) en4 = 0;
    
    for (int i = (int)x/10; i < en1; i++)
    {
        sExplFire ef;
        ef.x = i;
        ef.z = (int)z/10;
        explfire.append(ef);
        if (level->stages[(int)z/10].objects[i] == Object::BRIKS)
        {
            level->stages[(int)z/10].objects[i] = Object::NONE;
            level->stages[(int)z/10].collisionobj[i] = Object::NONE;
            break;
        }
        if (level->stages[(int)z/10].objects[i] == Object::CONCRETE) break;
        
    }
    for (int i = (int)x/10; i > en2; i--)
    {
        sExplFire ef;
        ef.x = i;
        ef.z = (int)z/10;
        explfire.append(ef);
        if (level->stages[(int)z/10].objects[i] == Object::BRIKS)
        {
            level->stages[(int)z/10].objects[i] = Object::NONE;
            level->stages[(int)z/10].collisionobj[i] = Object::NONE;
            break;
        }
        if (level->stages[(int)z/10].objects[i] == Object::CONCRETE) break;
    }
    for (int i = (int)z/10; i < en3; i++)
    {
        sExplFire ef;
        ef.x = (int)x/10;
        ef.z = i;
        explfire.append(ef);
        if (level->stages[i].objects[(int)x/10] == Object::BRIKS)
        {
            level->stages[i].objects[(int)x/10] = Object::NONE;
            level->stages[i].collisionobj[(int)x/10] = Object::NONE;
            break;
        }
        if (level->stages[i].objects[(int)x/10] == Object::CONCRETE) break;
    }
    for (int i = (int)z/10; i > en4; i--)
    {
        sExplFire ef;
        ef.x = (int)x/10;
        ef.z = i;
        explfire.append(ef);
        if (level->stages[i].objects[(int)x/10] == Object::BRIKS)
        {
            level->stages[i].objects[(int)x/10] = Object::NONE;
            level->stages[i].collisionobj[(int)x/10] = Object::NONE;
            break;
        }
        if (level->stages[i].objects[(int)x/10] == Object::CONCRETE) break;
    }
}

int Explosion::checkDamage(Model *_model)
{   
    for (int i = 0; i < explfire.count(); i ++)
    {
        if ((explfire[i].x == (int)(_model->x+5)/10) && (explfire[i].z == (int)(_model->z+5)/10))
        {
            return 100;
        }
    }
    return 0;
}

void Explosion::update()
{
    if (frame >= end)
    {
        endExpl = true;
    }
}

Explosion::~Explosion()
{
    
}

void Explosion::clear()
{
    
}
