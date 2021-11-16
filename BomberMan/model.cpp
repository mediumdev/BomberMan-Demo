#include "model.h"

Model::Model()
{
    end=0;
    start=0;
    animType = Animation::NONE;
    animate = true;
    cUp = false;
    cDown = false;
    cLeft = false;
    cRight = false;
    side = Side::RIGHT;
    x = 0;
    y = 0;
    z = 0;
    speed = 1.f;
            
    color = QVector4D(1.f,1.f,1.f,1.f);
}

Model::~Model()
{
    
}

bool Model::chekCollision(Level *level, int xx, int zz, Object::type _type)
{
    if ((level->stages[(zz+7)/10].collisionobj[(xx+7)/10] == _type)
            || (level->stages[(zz+3)/10].collisionobj[(xx+3)/10] == _type)
            || (level->stages[(zz+7)/10].collisionobj[(xx+3)/10] == _type)
            || (level->stages[(zz+3)/10].collisionobj[(xx+7)/10] == _type))
    {
        return false;
    }
    return true;
}

void Model::updateCollision(Level *level)
{
    cUp = false;
    cDown = false;
    cLeft = false;
    cRight = false;
    
    if (!chekCollision(level, x, z, Object::BLOCK)){
        if (!chekCollision(level, x+speed+0.5, z, Object::WALL)) cRight = true;
        if (!chekCollision(level, x-speed+0.5, z, Object::WALL)) cLeft = true;
        if (!chekCollision(level, x, z-speed+0.5, Object::WALL)) cUp = true;
        if (!chekCollision(level, x, z+speed+0.5, Object::WALL)) cDown = true;
    }
    else
    {
        if (!chekCollision(level, x+speed+0.5, z, Object::WALL) || !chekCollision(level, x+speed+0.5, z, Object::BLOCK)) cRight = true;
        if (!chekCollision(level, x-speed+0.5, z, Object::WALL) || !chekCollision(level, x-speed+0.5, z, Object::BLOCK)) cLeft = true;
        if (!chekCollision(level, x, z-speed+0.5, Object::WALL) || !chekCollision(level, x, z-speed+0.5, Object::BLOCK)) cUp = true;
        if (!chekCollision(level, x, z+speed+0.5, Object::WALL) || !chekCollision(level, x, z+speed+0.5, Object::BLOCK)) cDown = true;
    }
}

void Model::addAnimation(Animation::Type _type, float _start, float _end)
{
    AnimKeys ankey;
    ankey.type = _type;
    ankey.start = _start;
    ankey.end = _end;
    anim.append(ankey);
}

void Model::setPosition(float _x, float _y, float _z)
{
    x = _x;
    y = _y;
    z = _z;
}

void Model::setAngle(int _angle)
{
    angle = _angle;
}

void Model::playAnim(Animation::Type type, float _speed, bool _loop)
{
    speed = _speed;
    loop = _loop;
    if (anim.count()>0)
    {
        for (int i = 0; i < anim.count(); i ++)
        {
            animate = true;
            if ((anim[i].type == type) && (animType != type))
            {
                animType = type;
                start = anim[i].start;
                end = anim[i].end;
                frame = start;
            }
        }
    }
}

void Model::updateAnim()
{
    if (animate)
    {
        if (frame+speed<=end) frame+=speed;
        else
        {
            if (loop)
            {
                float excess = frame+speed-end;
                frame = start-1 + excess;
            }
            else
            {
                frame = end;
            }
        }
    }
}

void Model::stopAnim()
{
    animate = false;
}

void Model::clear()
{
    
}
