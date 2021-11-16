#ifndef PLAYER_H
#define PLAYER_H

#include "model.h"

namespace nPlayer
{
    enum Weapon
    {
        NONE, BOMB
    };
}

struct sPlayer
{
    float speed;
    float bombspeed;
    int healch;
    int power;
    int maxbombs;
    nPlayer::Weapon weapon;
};

class Player : public Model
{
private:

public:
    Player();
    virtual ~Player();
    
    void resurrect();
    void update();
    
    void clear();
    
    sPlayer splayer;
    bool dead;
    bool hit;
    bool restart;
};

#endif // PLAYER_H
