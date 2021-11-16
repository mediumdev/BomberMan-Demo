#include "enemy.h"

#include <QDebug>

Enemy::Enemy()
{

}

Enemy::~Enemy()
{
    
}

bool Enemy::collModel(Model *_model)
{
    if (walkingSide == 1)
    {
        if (((int)_model->x/10 == (int)(x+2)/10) && ((int)_model->z/10 == (int)z/10)) return true;
    }
    else if (walkingSide == 2)
    {
        if (((int)_model->x/10 == (int)(x+2)/10) && ((int)_model->z/10 == (int)(z-2)/10)) return true;
    }
    else if (walkingSide == 3)
    {
        if (((int)_model->x/10 == (int)x/10) && ((int)_model->z/10 == (int)(z-2)/10)) return true;
    }
    else if (walkingSide == 4)
    {
        if (((int)_model->x/10 == (int)(x-2)/10) && ((int)_model->z/10 == (int)(z-2)/10)) return true;
    }
    else if (walkingSide == 5)
    {
        if (((int)_model->x/10 == (int)(x-2)/10) && ((int)_model->z/10 == (int)z/10)) return true;
    }
    else if (walkingSide == 6)
    {
        if (((int)_model->x/10 == (int)(x-2)/10) && ((int)_model->z/10 == (int)(z+2)/10)) return true;
    }
    else if (walkingSide == 7)
    {
        if (((int)_model->x/10 == (int)x/10) && ((int)_model->z/10 == (int)(z+2)/10)) return true;
    }
    else if (walkingSide == 8)
    {
        if (((int)_model->x/10 == (int)(x+2)/10) && ((int)_model->z/10 == (int)(z+2)/10)) return true;
    }
    
    return false;
}

void Enemy::update()
{
    if (senemy.healch<=0)
    {
        dead = true;
        playAnim(Animation::DIE, 1.f, false);
    }
    else
    {
        if (cPlayer)
        {
            blow = true;
            walking = false;
            playAnim(Animation::BLOW, 1.f, true);
        }
        else
        {
            if (((int)frame >= (int)end) && (blow))
            {
                blow = false;
                walking = true;
            }
        }
        if (!blow) walk();
    }
    //qDebug() << cPlayer;
}

void Enemy::walk()
{
    if (!walking)
    {
        playAnim(Animation::STAY, 1.f, true);
        walking = true;
        walkingSide = qrand() % ((8 + 1) - 1) + 1;
    }
    else
    {
        setAngle((walkingSide-1)*45);
        if ((walkingSide==1) || (walkingSide==2) || (walkingSide==8))
        {
            if (!cRight)
            {
                setPosition(x+(float)senemy.speed/2,y,z);
                playAnim(Animation::RUN, speed, true);
            }
            else
            {
                walking = false;
            }
        }
        if ((walkingSide==2) || (walkingSide==3) || (walkingSide==4))
        {
            if (!cUp)
            {
                setPosition(x,y,z-(float)senemy.speed/2);
                playAnim(Animation::RUN, speed, true);
            }
            else
            {
                walking = false;
            }
        }
        if ((walkingSide==4) || (walkingSide==5) || (walkingSide==6))
        {
            if (!cLeft)
            {
                setPosition(x-(float)senemy.speed/2,y,z);
                playAnim(Animation::RUN, speed, true);
            }
            else
            {
                walking = false;
            }
        }
        if ((walkingSide==6) || (walkingSide==7) || (walkingSide==8))
        {
            if (!cDown)
            {
                setPosition(x,y,z+(float)senemy.speed/2);
                playAnim(Animation::RUN, speed, true);
            }
            else
            {
                walking = false;
            }
        }
        
    }
}

void Enemy::clear()
{
    
}
