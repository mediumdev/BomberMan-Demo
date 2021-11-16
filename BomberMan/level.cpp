#include "level.h"

#include <QFile>
#include <QTextStream>

Level::Level()
{
    loaded = false;
}

Level::Level(QString path, QString filename)
{
    loaded = false;
    
    load(path, filename);
}

Level::~Level()
{
    clear();
}

Object::type Level::getObject(int x, int y)
{
    return stages[y].objects[x];
}

void Level::setObject(int x, int y, Object::type obj)
{
    stages[y].objects[x] = obj;
}

Object::type Level::getCollObject(int x, int y)
{
    return stages[y].collisionobj[x];
}

void Level::setCollObject(int x, int y, Object::type obj)
{
    stages[y].collisionobj[x] = obj;
}

bool Level::load(QString path, QString filename)
{
    QFile file (path + "/" + filename + ".lvl");
    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        QString line="";
        
        int numline=0;
        
        while (!stream.atEnd())
        {
            line = stream.readLine();
            line = line.simplified();
            if ((line!="")||(line!=" "))
            {
                MapStage obj;
                for (int i = 0; i<line.count(); i++)
                {
                    if (line[i]=='c')
                    {
                        obj.objects.append(Object::CONCRETE);
                        obj.collisionobj.append(Object::WALL);
                    }
                    else if (line[i]=='b')
                    {
                        obj.objects.append(Object::BRIKS);
                        obj.collisionobj.append(Object::WALL);
                    }
                    else if (line[i]=='r')
                    {
                        obj.objects.append(Object::NONE);
                        obj.collisionobj.append(Object::NONE);
                        playerResp.x = i*10;
                        playerResp.z = numline*10;
                        playerResp.type = Object::RESP;
                    }
                    else if (line[i]=='z')
                    {
                        obj.objects.append(Object::NONE);
                        obj.collisionobj.append(Object::NONE);
                        Resp r;
                        r.x = i*10;
                        r.z = numline*10;
                        r.type = Object::ZOMBIE;
                        respown.append(r);
                    }
                    else
                    {
                        obj.objects.append(Object::NONE);
                        obj.collisionobj.append(Object::NONE);
                    }
                }
                stages.append(obj);
                numline ++;
            }
        }
        if(stream.status()!= QTextStream::Ok)
        {
            return false;
        }
        file.close();
        loaded = true;
        return true;
    }
    return false;
}

void Level::clear()
{
    respown.clear();
    for (int i = 0; i < stages.count(); i++)
    {
        stages[i].objects.clear();
        stages[i].collisionobj.clear();
    }
    stages.clear();
}
