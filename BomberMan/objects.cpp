#include "objects.h"

Objects::Objects()
{
    
}

Objects::Objects(QGLWidget *qglwidget)
{
    s_textured = new Shader(":/shaders", "textured", qglwidget);
}

Objects::~Objects()
{
    clear();
}

int Objects::addMesh(Mesh *mesh)
{
    Meshes msh;
    msh.mesh = mesh;
    meshes.append(msh);
    return meshes.count()-1;
}

void Objects::addParam(QMatrix4x4 orient, int frame, QVector4D color, int index)
{
    Param par;
    par.orient = orient;
    par.frame = frame;
    par.color = color;
    meshes[index].params.append(par);
    meshes[index].oneframe = false;
}

void Objects::draw(Camera *camera)
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    s_textured->bind();
    s_textured->setUniform("proj", camera->projection);
    
    for (int i = 0; i < meshes.count(); i++)
    {
        lastframe = -1;
        
        s_textured->setUniform("tex", meshes[i].mesh->texture);
        s_textured->setAttribute("texCoord", meshes[i].mesh->texcoords.data(), 2);
        
        for (int j = 0; j < meshes[i].params.count(); j++)
        {
            if (lastframe != meshes[i].params[j].frame)
            {
                lastframe = meshes[i].params[j].frame;
                s_textured->setAttribute("vertex", meshes[i].mesh->frames[meshes[i].params[j].frame].verts.data());
            }
            s_textured->setUniform("color", meshes[i].params[j].color);
            s_textured->setUniform("matrix", meshes[i].params[j].orient);
            glDrawElements(GL_TRIANGLES, meshes[i].mesh->num_tris*3, GL_UNSIGNED_SHORT, meshes[i].mesh->inds.data());
        }
    }
    s_textured->disableAttribute("vertex");
    s_textured->disableAttribute("texCoord");
    s_textured->release();
    
    glDisable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
}

void Objects::clear()
{
    meshes.clear();
}
