#include "shader.h"

Shader::Shader(QGLWidget *qglwidget)
{
    loaded=false;
    glwidget = qglwidget;
}

Shader::Shader(QString path, QString filename, QGLWidget *qglwidget)
{
    loaded=false;
    glwidget = qglwidget;
    
    load(path, filename);
}

Shader::~Shader()
{
    clear();
}

bool Shader::load(QString path, QString filename)
{
    QGLShader *vertex_shader = new QGLShader(QGLShader::Vertex, glwidget);
    vertex_shader->compileSourceFile(path + "/" + filename + ".vsh");
    QGLShader *fragment_shader = new QGLShader(QGLShader::Fragment, glwidget);
    fragment_shader->compileSourceFile(path + "/" + filename + ".fsh");

    sampleProgram.addShader(vertex_shader);
    sampleProgram.addShader(fragment_shader);
    if (!sampleProgram.link())
    {
        clear();
        
        delete vertex_shader;
        delete fragment_shader;
        
        return false;
    }
    loaded=true;
    
    delete vertex_shader;
    delete fragment_shader;
    
    return true;
}

void Shader::bind()
{
    sampleProgram.bind();
}

void Shader::setUniform(const char *name, QMatrix4x4 value)
{
    sampleProgram.setUniformValue(name, value);
}

void Shader::setUniform(const char *name, QVector4D value)
{
    sampleProgram.setUniformValue(name, value);
}

void Shader::setUniform(const char *name, float value)
{
    sampleProgram.setUniformValue(name, value);
}

void Shader::setUniform(const char *name, uint value)
{
    glBindTexture(GL_TEXTURE_2D, value);
    sampleProgram.setUniformValue(name, 0);
}

void Shader::setAttribute(const char *name, const float *value, int tupleSyze)
{
    sampleProgram.enableAttributeArray(name);
    sampleProgram.setAttributeArray(name, value, tupleSyze);
}

void Shader::setAttribute(const char *name, const QVector3D *value)
{
    sampleProgram.enableAttributeArray(name);
    sampleProgram.setAttributeArray(name, value);
}

void Shader::disableAttribute(const char *name)
{
    sampleProgram.disableAttributeArray(name);
}

void Shader::release()
{
    sampleProgram.release();
}

void Shader::clear()
{
    
}
