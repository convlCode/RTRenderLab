#ifndef SHADER_H
#define SHADER_H

#include <QOpenGLShaderProgram>
#include <QString>

class Shader
{
public:
    Shader(const QString& vertexSourcePath,const QString& fragmentSourcePath);
    ~Shader();

    QOpenGLShaderProgram shaderProgram;

    void use(){
        shaderProgram.bind();
    }
};

#endif // SHADER_H
