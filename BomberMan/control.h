#ifndef CONTROL_H
#define CONTROL_H

#include <QVector>
#include "player.h"
#include "touch.h"
#include "trackball.h"

namespace Keyboard
{
    enum key {
        NONE, UP, DOWN, LEFT, RIGHT, A, B, MENU
    };
}

class Control
{
private:
    QVector<Keyboard::key> keys;
    QVector<Point> points;
    
    
    
    void updateActions();
public:
    Control();
    ~Control();
    void update(QVector<Point> &touchpoints);
    void update(QVector<Keyboard::key> &_keys, TrackBall *trackball);
    void setPlayer(Player *_player);
    
    void clear();
    
    bool kUp;
    bool kDown;
    bool kLeft;
    bool kRight;
    bool kA;
    bool kB;
    
    Player *player;
};

#endif // CONTROL_H
