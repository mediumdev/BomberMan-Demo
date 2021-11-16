#include "mesh.h"
#include <fstream>
#include <QFile>
#include <QTextStream>
#include <QStringList>

Mesh::Mesh()
{
    loaded = false;
    animated = false;
    num_frames = 0;
    num_tris = 0;
    num_verts = 0;
    texture = 0;
}

Mesh::Mesh(QString path, QString filename)
{
    loaded = false;
    animated = false;
    num_frames = 0;
    num_tris = 0;
    num_verts = 0;
    texture = 0;
    
    load(path, filename);
}

Mesh::~Mesh()
{
    Clear();
}

bool Mesh::load(QString path, QString filename)
{
    QFile file (path + "/" + filename + ".sm");
    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        QString str;
        QString curr="";

        int curline = 0;
        int numline = 0;
        int curr_frame = 0;
        while (!stream.atEnd())
        {
            str = stream.readLine();
            str = str.simplified();
            if ((str!="")||(str!=" "))
            {
                QStringList words = str.split(" ");
                if ((words[0]=="texs")||(words[0]=="tris")||(words[0]=="numframes")||(words[0]=="frame"))
                {
                    if (words[0]=="texs") {
                        texcoords.reserve(words[1].toInt()*2);
                        num_verts = words[1].toInt();
                        numline = words[1].toInt();
                        curr = words[0];
                        curline = 0;
                    }
                    else if (words[0]=="tris") {
                        inds.reserve(words[1].toInt()*3);
                        num_tris = words[1].toInt();
                        numline = words[1].toInt();
                        curr = words[0];
                        curline = 0;
                    }
                    else if (words[0]=="numframes") {
                        num_frames = words[1].toInt();
                        if (num_frames>1) animated=true;
                        frames.resize(num_frames);
                    }
                    else if (words[0]=="frame") {
                        frames[words[1].toInt()].verts.reserve(num_verts);
                        curr_frame = words[1].toInt();
                        numline = num_verts;
                        curr = words[0];
                        curline = 0;
                    }
                }
                else{
                    if ((curline<numline)&&(curr=="texs")){
                        texcoords.append(words[0].toFloat());
                        texcoords.append(words[1].toFloat());
                        curline++;
                    }
                    else if ((curline<numline)&&(curr=="tris")){
                        inds.append(words[0].toShort());
                        inds.append(words[1].toShort());
                        inds.append(words[2].toShort());
                        curline++;
                    }
                    else if ((curline<numline)&&(curr=="frame")){
                        frames[curr_frame].verts.append(QVector3D(words[0].toFloat(),words[1].toFloat(),words[2].toFloat()));
                        curline++;
                    }
                }
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

void Mesh::Clear()
{
    texcoords.clear();
    inds.clear();

    for (int i = 0; i < frames.count(); i++)
    {
        frames[i].verts.clear();
    }
    frames.clear();
}
