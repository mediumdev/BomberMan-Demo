#include "player.h"

#include <QDebug>

Player::Player()
{
    addAnimation(Animation::STAY,1,31);
    addAnimation(Animation::DIE,31,51);
    addAnimation(Animation::RUN,52,76);
    addAnimation(Animation::HIT,30,35);
    
    splayer.speed = 1.0f;
    splayer.bombspeed = 0.7f;
    splayer.healch = 100;
    splayer.power = 1;
    splayer.maxbombs = 1;
    dead = false;
    hit = false;
    restart = false;
    
    splayer.weapon = nPlayer::BOMB;
}

Player::~Player()
{
    clear();
}


void Player::resurrect()
{
    splayer.speed = 1.0f;
    splayer.bombspeed = 0.7f;
    splayer.healch = 100;
    splayer.power = 1;
    splayer.maxbombs = 1;
    dead = false;
    hit = false;
    restart = false;
    
    splayer.weapon = nPlayer::BOMB;
}

void Player::update()
{
    if (splayer.healch<=0)
    {
        dead = true;
        playAnim(Animation::DIE, 1.f, false);
        if ((int)frame >= (int)end) {
            restart = true;
        }
    }
    else
    {
        if (hit)
        {
            playAnim(Animation::HIT, 1.f, false);
            if ((int)frame >= (int)end) {
                splayer.healch -=10;
                hit = false;
                playAnim(Animation::STAY, 1.f, true);
            }
        }
    }
    //qDebug() << splayer.healch;
}

void Player::clear()
{
    
}
