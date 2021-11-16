#ifndef GAME_H
#define GAME_H

#include "camera.h"
#include "touch.h"
#include "mesh.h"
#include "texture.h"
#include "control.h"
#include "level.h"
#include "player.h"
#include "shader.h"
#include "objects.h"
#include "image.h"
#include "trackball.h"
#include "bomb.h"
#include "explosion.h"
#include "zombie.h"

class Game
{
private:
    QVector<Point> points;
    QVector<Keyboard::key> keys;
public:
    Game(QGLWidget *qglwidget);
    ~Game();

    void init();
    void resize();
    void update();
    void draw();
    void restart();
    void loadLevel(QString path, QString filename);
    void touchUpdate(QVector<Point> &touchpoints);
    void keyUpdate(QVector<Keyboard::key> &_keys);
    bool onScreen(int _x, int _y, int _width, int _height);
    
    void clear();
    
    QGLWidget *glwidget;
    
    int fps;
    int aps;
    bool pause;
    
    Camera *camera;
    Control *control;
    Objects *objects;
    Image *images;
    TrackBall *trackball;
    
    Level *level;
    
    Mesh *m_briks;
    Mesh *m_concrete;
    Mesh *m_floor;
    Mesh *m_player;
    Mesh *m_bomb;
    Mesh *m_explosion;
    Mesh *m_zombie;
    
    Texture *t_briks;
    Texture *t_concrete;
    Texture *t_player;
    Texture *t_bomb;
    Texture *t_explosion;
    Texture *t_zombie;
    
    Player *player;
    QVector<Bomb> bombs;
    QVector<Explosion> explosions;
    QVector<Zombie> zombies;
};

#endif // GAME_H
