﻿#ifndef SHADER_H
#define SHADER_H

#include <QOpenGLShaderProgram>
#include <QString>

class Shader
{
    friend class ResourceManager;
public:
    Shader(){}
    //Shader(const QString& vertexSourcePath,const QString& fragmentSourcePath);
    void compile(const QString& vertexSource, const QString& fragmentSource, const QString& geometrySource = nullptr);
    ~Shader();

    QOpenGLShaderProgram* shaderProgram;

    Shader& use(){
        shaderProgram->bind();
        return *this;
    }
    inline void setMatrix4f(const QString& name,const QMatrix4x4& value);
    inline void setInteger(const QString& name,const GLint value);
};

inline void Shader::setMatrix4f(const QString &name, const QMatrix4x4 &value)
{
    GLint loc = shaderProgram->uniformLocation(name);
    shaderProgram->setUniformValue(loc,value);
}

inline void Shader::setInteger(const QString &name, const GLint value)
{
    GLint loc = shaderProgram->uniformLocation(name);
    shaderProgram->setUniformValue(loc,value);
}

#endif // SHADER_H
