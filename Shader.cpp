#include "Shader.h"
#include <QDebug>

Shader::Shader(const QString& vertexSourcePath,const QString& fragmentSourcePath)
{
    QOpenGLShader vertexShader(QOpenGLShader::Vertex);
    bool success = vertexShader.compileSourceFile(vertexSourcePath);
    if(!success){
        qDebug()<<"ERROR::SHADER::VERTEX::COMPILATION_FAILED" << endl;
        qDebug()<<vertexShader.log() << endl;
    }
    QOpenGLShader fragmentShader(QOpenGLShader::Fragment);
    success = fragmentShader.compileSourceFile(fragmentSourcePath);
    if(!success){
        qDebug() << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED" << endl;
        qDebug() << fragmentShader.log() << endl;
    }

    shaderProgram.addShader(&vertexShader);
    shaderProgram.addShader(&fragmentShader);
    success=shaderProgram.link();
    if(!success){
        qDebug() << "ERROR::SHADER::PROGRAM::LINKING_FAILED" << endl;
        qDebug() << shaderProgram.log() << endl;
    }
}

Shader::~Shader()
{

}
