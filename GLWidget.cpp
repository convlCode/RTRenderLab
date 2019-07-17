#include "GLWidget.h"
#include <QImage>

GLWidget::GLWidget(QWidget* parent,Qt::WindowFlags f)
    :QOpenGLWidget(parent, f)
{

}

GLWidget::~GLWidget()
{
    delete myShader;
    core->glDeleteVertexArrays(1,&VAO);
    core->glDeleteBuffers(1,&VBO);
    core->glDeleteBuffers(1,&EBO);

    //texture->destroy();
}

void GLWidget::initializeGL()
{
    core = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>();
    myShader = new Shader(":/shaders/vertexShaderSource.vs",":/shaders/fragShaderSource.fs");

    GLfloat vertices[] = {
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
       -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
       -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
    };

    GLuint indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    core->glGenVertexArrays(1, &VAO);
    core->glGenBuffers(1, &VBO);
    core->glGenBuffers(1,&EBO);

    core->glBindVertexArray(VAO);

    core->glBindBuffer(GL_ARRAY_BUFFER, VBO);
    core->glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    core->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    core->glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

    core->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), reinterpret_cast<void*>(0));
    core->glEnableVertexAttribArray(0);

    core->glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8 * sizeof(GLfloat),reinterpret_cast<void*>(3*sizeof(GLfloat)));
    core->glEnableVertexAttribArray(1);

    core->glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(GLfloat),reinterpret_cast<void*>(6*sizeof(GLfloat)));
    core->glEnableVertexAttribArray(2);

    texture1 = new QOpenGLTexture(QOpenGLTexture::Target2D);
    texture1->setFormat(QOpenGLTexture::RGBFormat);
    QImage img(":/textures/container.jpg");
    texture1->setData(img.mirrored(),QOpenGLTexture::GenerateMipMaps);
    if(!texture1->isCreated()){
        qDebug() << "Failed to load texture" << endl;
    }
    texture1->setWrapMode(QOpenGLTexture::DirectionS,QOpenGLTexture::Repeat);
    texture1->setWrapMode(QOpenGLTexture::DirectionT,QOpenGLTexture::Repeat);

    texture1->setMinificationFilter(QOpenGLTexture::Linear);
    texture1->setMagnificationFilter(QOpenGLTexture::Linear);

    texture2 = new QOpenGLTexture(QOpenGLTexture::Target2D);
    texture2->setFormat(QOpenGLTexture::RGBAFormat);
    QImage img2(":/textures/smileface.png");
    texture2->setData(img2.mirrored(),QOpenGLTexture::GenerateMipMaps);
    if(!texture2->isCreated()){
        qDebug() << "Failed to load texture" << endl;
    }
    texture2->setWrapMode(QOpenGLTexture::DirectionS,QOpenGLTexture::Repeat);
    texture2->setWrapMode(QOpenGLTexture::DirectionT,QOpenGLTexture::Repeat);
    texture2->setMinificationFilter(QOpenGLTexture::Linear);
    texture2->setMagnificationFilter(QOpenGLTexture::Linear);

    myShader->use();
    myShader->shaderProgram.setUniformValue(myShader->shaderProgram.uniformLocation("texture1"),0);
    myShader->shaderProgram.setUniformValue(myShader->shaderProgram.uniformLocation("texture2"),1);

    //time.start();
    QMatrix4x4 model,view,projection;
    model.rotate(-55.0f,QVector3D(1.0f,0.0f,0.0f));
    view.translate(QVector3D(0.0f,0.0f,-3.0f));
    projection.perspective(45.0f,static_cast<float>(width())/static_cast<float>(height()),0.1f,100.0f);

    myShader->use();
    myShader->setMat4("model",model);
    myShader->setMat4("view",view);
    myShader->setMat4("projection",projection);
}

void GLWidget::resizeGL(int w, int h)
{
    core->glViewport(0,0,w,h);
}

void GLWidget::paintGL()
{
    core->glClearColor(0.2f,0.3f,0.3f,1.0f);
    core->glClear(GL_COLOR_BUFFER_BIT);

    core->glActiveTexture(GL_TEXTURE0);
    texture1->bind();
    core->glActiveTexture(GL_TEXTURE1);
    texture2->bind();

    myShader->use();
    core->glBindVertexArray(VAO);
    //core->glDrawArrays(GL_TRIANGLES, 0, 3);
    //core->glUseProgram(0);
    core->glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,reinterpret_cast<GLvoid*>(0));
    update();
}
