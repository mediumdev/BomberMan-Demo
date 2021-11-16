#ifndef SHADER_H
#define SHADER_H

#include <QString>
#include <QVector3D>
#include <QtOpenGL>
#include <QMatrix4x4>

class Shader
{
private:
    QGLShaderProgram sampleProgram;
public:
    Shader(QGLWidget *qglwidget);
    Shader(QString path, QString filename, QGLWidget *qglwidget);
    ~Shader();

    bool load(QString path, QString filename);

    void bind();
    void setUniform(const char *name, QMatrix4x4 value);
    void setUniform(const char *name, QVector4D value);
    void setUniform(const char *name, float value);
    void setUniform(const char *name, uint value);
    void setAttribute(const char *name, const float *value, int tupleSyze);
    void setAttribute(const char *name, const QVector3D *value);
    void disableAttribute(const char *name);
    void release();

    void clear();
    
    QGLWidget *glwidget;

    bool loaded;
};

#endif // SHADER_H
