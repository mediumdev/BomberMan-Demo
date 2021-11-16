#include "control.h"

Control::Control()
{
    kUp=false;
    kDown=false;
    kLeft=false;
    kRight=false;
    kA=false;
    kB=false;
}

Control::~Control()
{
    clear();
}

void Control::setPlayer(Player *_player)
{
    player = _player;
}

void Control::update(QVector<Point> &touchpoints)
{
    points.clear();
    points = touchpoints;
    
    if (points.count()>0)
    {
        
    }
}

void Control::update(QVector<Keyboard::key> &_keys, TrackBall *trackball)
{
    keys.clear();
    keys = _keys;
    
    kUp=false;
    kDown=false;
    kLeft=false;
    kRight=false;
    kA=false;
    kB=false;
    
    for (int i = 0; i < keys.count(); i++)
    {
        if (keys[i]==Keyboard::RIGHT)
        {
            kRight = true;
        }
        if (keys[i]==Keyboard::LEFT)
        {
            kLeft = true;
        }
        if (keys[i]==Keyboard::UP)
        {
            kUp = true;
        }
        if (keys[i]==Keyboard::DOWN)
        {
            kDown = true;
        }
        if (keys[i]==Keyboard::A)
        {
            kA = true;
        }
        if (keys[i]==Keyboard::B)
        {
            kB = true;
        }
        if (keys[i]==Keyboard::MENU)
        {
            exit(0);
        }
    }
    
    if ((trackball->pangle>-1) && (trackball->enable))
    {
        if ((trackball->pangle>=22)&&(trackball->pangle<=157))
        {
            kRight = true;
        }
        if ((trackball->pangle>=202)&&(trackball->pangle<=337))
        {
            kLeft = true;
        }
        if ((trackball->pangle>=112)&&(trackball->pangle<=247))
        {
            kUp = true;
        }
        if (((trackball->pangle>=292)&&(trackball->pangle<=359)) || ((trackball->pangle>=1)&&(trackball->pangle<=67)))
        {
            kDown = true;
        }
    }  
    
    if ((!kRight)&&(!kLeft)&&(!kUp)&&(!kDown))
    {
        player->playAnim(Animation::STAY, 1, true);
    }
    
    
    updateActions();
    
    if (kRight)
    {
        if (!player->cRight)
        {
            player->setPosition(player->x+(float)player->splayer.speed/2,player->y,player->z);
        }
        player->side = Side::RIGHT;
        if ((!kUp)&&(!kDown)) player->setAngle(0);
        else
        {
            if (kUp) player->setAngle(45);
            else if (kDown) player->setAngle(315);
        }
        player->playAnim(Animation::RUN, player->splayer.speed, true);
    }
    if (kLeft)
    {
        if (!player->cLeft)
        {
            player->setPosition(player->x-(float)player->splayer.speed/2,player->y,player->z);
        }
        player->side = Side::LEFT;
        if ((!kUp)&&(!kDown)) player->setAngle(180);
        else
        {
            if (kUp) player->setAngle(135);
            else if (kDown) player->setAngle(225);
        }
        player->playAnim(Animation::RUN, player->splayer.speed, true);
    }
    if (kUp)
    {
        if (!player->cUp)
        {
            player->setPosition(player->x,player->y,player->z-(float)player->splayer.speed/2);
        }
        player->side = Side::UP;
        if ((!kRight) && (!kLeft)) player->setAngle(90);
        player->playAnim(Animation::RUN, player->splayer.speed, true);
    }
    if (kDown)
    {
        if (!player->cDown)
        {
            player->setPosition(player->x,player->y,player->z+(float)player->splayer.speed/2);
        }
        
        player->side = Side::DOWN;
        if ((!kRight) && (!kLeft)) player->setAngle(270);
        player->playAnim(Animation::RUN, player->splayer.speed, true);
    }
    if (kA)
    {
        
    }
    if (kB)
    {  
        
    }
}

void Control::updateActions()
{

}

void Control::clear()
{
    
}
