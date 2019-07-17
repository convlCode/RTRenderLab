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
    inline void setMat4(const QString& name,const QMatrix4x4& value);
    inline void setInt(const QString& name,const GLint value);
};

inline void Shader::setMat4(const QString &name, const QMatrix4x4 &value)
{
    GLint loc = shaderProgram.uniformLocation(name);
    shaderProgram.setUniformValue(loc,value);
}

inline void Shader::setInt(const QString &name, const GLint value)
{
    GLint loc = shaderProgram.uniformLocation(name);
    shaderProgram.setUniformValue(loc,value);
}

#endif // SHADER_H
