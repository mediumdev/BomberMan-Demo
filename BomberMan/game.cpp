#include "game.h"

int tbIndex;
int tbposIndex;
int tb1Index;

Game::Game(QGLWidget *qglwidget)
{
    glwidget = qglwidget;
}

Game::~Game()
{
    clear();
}

void Game::init()
{
    camera = new Camera(glwidget);
    camera->perspective(45.0f, (float)glwidget->width()/(float)glwidget->height(), 0.1f, 350.0f);
    camera->rotate(60, 1, 0, 0);
    //camera->clearColor(0.5f, 0.5f, 0.9f, 1.0f);
    camera->clearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    control = new Control();
    objects = new Objects(glwidget);
    images = new Image(glwidget);
    

    //loading
    //--------------------------------------------------------------------//
    
    m_player = new Mesh(":/models", "player");
    t_player = new Texture(":/textures", "player", glwidget);
    m_player->texture = t_player->texture;
    player = new Player();
    control->setPlayer(player);
    
    m_bomb = new Mesh(":/models", "bomb");
    t_bomb = new Texture(":/textures", "bomb", glwidget);
    m_bomb->texture = t_bomb->texture;
    
    m_explosion = new Mesh(":/models", "explosion");
    t_explosion = new Texture(":/textures", "explosion", glwidget);
    m_explosion->texture = t_explosion->texture;
    
    m_briks = new Mesh(":/models", "briks");
    t_briks = new Texture(":/textures", "briks", glwidget);
    m_briks->texture = t_briks->texture;
    
    m_concrete = new Mesh(":/models", "concrete");
    t_concrete = new Texture(":/textures", "concrete", glwidget);
    m_concrete->texture = t_concrete->texture;
    
    m_floor = new Mesh(":/models", "floor");
    m_floor->texture = t_concrete->texture;
    
    m_zombie = new Mesh(":/models", "zombie");
    t_zombie = new Texture(":/textures", "zombie", glwidget);
    m_zombie->texture = t_zombie->texture;
    
    tb1Index = images->addImage(":/textures", "trackball01");
    images->addPos(20,glwidget->height()-images->imgList[tb1Index].img.height-20,tb1Index);
    trackball = new TrackBall(20,glwidget->height()-images->imgList[tb1Index].img.height-20,images->imgList[tb1Index].img.width,images->imgList[tb1Index].img.height);
    tbIndex = images->addImage(":/textures", "trackball");
    tbposIndex = images->addPos(20+48,glwidget->height()-images->imgList[tb1Index].img.height-20+48,tbIndex);
    
    loadLevel(":/levels", "level01");
    
    //--------------------------------------------------------------------//
    //end loading
}

void Game::loadLevel(QString path, QString filename)
{
    level = new Level(path, filename);
    player->setPosition(level->playerResp.x,0.f,level->playerResp.z);
    
    for (int i = 0; i < level->respown.count(); i++)
    {
        if (level->respown[i].type == Object::ZOMBIE)
        {
            zombies.append(Zombie());
            zombies.last().setPosition(level->respown[i].x,0.f,level->respown[i].z);
        }
    }
}

void Game::resize()
{
    camera->perspective(45.0f, (float)glwidget->width()/(float)glwidget->height(), 0.1f, 350.0f);
}

void Game::update()
{
    //update objects
    //--------------------------------------------------------------------//
    
    //player
    
    if (points.count()>0)
    {
        if ((points[0].state == Qt::TouchPointMoved) || (points[0].mouseState == 1) || (points[0].state == Qt::TouchPointPressed) || (points[0].mouseState == 2))
        {
            trackball->setTrackPos(points[0].x,points[0].y);
            if (trackball->enable) images->setPos(trackball->px-images->imgList[tbIndex].img.width/2, trackball->py-images->imgList[tbIndex].img.height/2, tbIndex, tbposIndex);
        }
        else
        {
            trackball->enable = false;
            trackball->pangle = -1;
            images->setPos(20+48,glwidget->height()-images->imgList[tb1Index].img.height-20+48, tbIndex, tbposIndex);
        }
    }
    
    
    if (!player->dead)
    {
        player->updateCollision(level);
        if (!player->hit)
        {
            control->update(keys, trackball);
            control->update(points);
        }
    }
    if (player->restart) restart();
    player->updateAnim();
    player->update();
    
    //bomb
    if (control->kA) 
    {
        if (level->getCollObject((int)(player->x+5)/10, (int)(player->z+5)/10) != Object::BLOCK)
        {
            bombs.append(Bomb((int)(player->x+5)/10*10, 0, (int)(player->z+5)/10*10, player->splayer.bombspeed,player->splayer.power));
            level->setCollObject((int)(player->x+5)/10, (int)(player->z+5)/10, Object::BLOCK);
        }
    }
    
    for (int i = 0; i<bombs.count(); i++)
    {
        if (!bombs[i].explode)
        {
            bombs[i].updateAnim();
            bombs[i].update();
        }
        else
        {
            level->setCollObject((int)(bombs[i].x+5)/10, (int)(bombs[i].z+5)/10, Object::NONE);
            explosions.append(Explosion(bombs[i].x,bombs[i].y,bombs[i].z,1.0f,bombs[i].sbomb.power,level));
            player->splayer.healch -= explosions.last().checkDamage((Model*)player);
            for (int i = 0; i < zombies.count(); i++)
            {
                zombies[i].senemy.healch -= explosions.last().checkDamage((Model*)&zombies[i]);
            }
            bombs.remove(i);
        }
    }

    //explosion
    for (int i = 0; i<explosions.count(); i++)
    {
        if (!explosions[i].endExpl)
        {
            explosions[i].updateAnim();
            explosions[i].update();
        }
        else
        {
            explosions.remove(i);
        }
    }
    //zombies
    for (int i = 0; i < zombies.count(); i++)
    {
        if (!zombies[i].dead)
        {
            zombies[i].cPlayer = false;
            if ((zombies[i].collModel((Model*)player)) && (!player->dead))
            {
                zombies[i].cPlayer = true;
                if ((!player->hit) && ((int)zombies[i].frame == (int)zombies[i].start)) player->hit = true;
            }
            zombies[i].updateCollision(level);
            zombies[i].update();
            
        }
        zombies[i].updateAnim();
    }
    
    //--------------------------------------------------------------------//
    //end update objects
    camera->goTo(0-player->x, player->y-55, 0-player->z-30);
}

void Game::draw()
{
    camera->begin();
    objects->clear();
    
    int briksIndex = objects->addMesh(m_briks);
    int concreteIndex = objects->addMesh(m_concrete);
    int floorIndex = objects->addMesh(m_floor);
    int playerIndex = objects->addMesh(m_player);
    int bombIndex = objects->addMesh(m_bomb);
    int explIndex = objects->addMesh(m_explosion);
    int zombieIndex = objects->addMesh(m_zombie);
    
    int i_start = 0;
    int i_end = 0;
    int j_start = 0;
    int j_end = 0;
    
    if (player->z/10-5>=0) i_start = player->z/10-5;
    else i_start = 0;
    if (player->z/10+4<=level->stages.count()-1) i_end = player->z/10+4;
    else i_end = level->stages.count();
    
    if (player->x/10-6>=0) j_start = player->x/10-6;
    else j_start = 0;
    if (player->x/10+8<=level->stages[0].objects.count()-1) j_end = player->x/10+8;
    else j_end = level->stages[0].objects.count();
    
    QMatrix4x4 orient;
    orient.setToIdentity();
    orient.translate(player->x, 0, player->z);
    orient.rotate(player->angle, 0, 1, 0);
    objects->addParam(orient, player->frame, player->color, playerIndex);
    for (int i = i_start; i < i_end; i++)
    {
        for (int j = j_start; j < j_end; j++)
        {
            if (level->stages[i].objects[j] != Object::RESP)
            {
                orient.setToIdentity();
                orient.translate(j*10, 0, i*10);
                if (level->stages[i].objects[j] == Object::BRIKS) objects->addParam(orient, 0, QVector4D(1.f,1.f,1.f,1.f), briksIndex);
                else if (level->stages[i].objects[j] == Object::CONCRETE) objects->addParam(orient, 0, QVector4D(1.f,1.f,1.f,1.f), concreteIndex);
                else if (level->stages[i].objects[j] == Object::NONE) objects->addParam(orient, 0, QVector4D(1.f,1.f,1.f,1.f), floorIndex);
            }
        }
    }
    //drawing objects
    //--------------------------------------------------------------------//
    
    //bomb
    for (int i = 0; i<bombs.count(); i++)
    {
        if (onScreen(bombs[i].x, bombs[i].z, 10, 10))
        {
            orient.setToIdentity();
            orient.translate(bombs[i].x, 0, bombs[i].z);
            objects->addParam(orient, bombs[i].frame, bombs[i].color, bombIndex);
        }
    }
    
    //explosion
    for (int i = 0; i<explosions.count(); i++)
    {
        if (onScreen(explosions[i].x, explosions[i].z, 10, 10))
        {
            orient.setToIdentity();
            orient.translate(explosions[i].x, 0, explosions[i].z);
            orient.scale((float)explosions[i].sexpl.power);
            objects->addParam(orient, explosions[i].frame, QVector4D(1.f,1.f,1.f,0.8f), explIndex);
        }
    }
    //zombies
    for (int i = 0; i < zombies.count(); i++)
    {
        if (onScreen(zombies[i].x, zombies[i].z, 10, 10))
        {
            orient.setToIdentity();
            orient.translate(zombies[i].x, 0, zombies[i].z);
            orient.rotate(zombies[i].angle, 0, 1, 0);
            objects->addParam(orient, zombies[i].frame, zombies[i].color, zombieIndex);
        }
    }
    //--------------------------------------------------------------------//
    //end drawing objects
    objects->draw(camera);
    images->draw();
}

bool Game::onScreen(int _x, int _y, int _width, int _height)
{
    if ((_x-5>player->x-50) && (_x-5<player->x+40) && (_y-5>player->y-60) && (_y-5<player->y+80))
    {
        return true;
    }
    return false;
}

void Game::restart()
{
    level->clear();
    zombies.clear();
    bombs.clear();
    explosions.clear();
    loadLevel(":/levels", "level01");
    player->resurrect();
}

void Game::touchUpdate(QVector<Point> &touchpoints)
{
    points.clear();
    points = touchpoints;
}

void Game::keyUpdate(QVector<Keyboard::key> &_keys)
{
    keys.clear();
    keys = _keys;
}

void Game::clear()
{

}
