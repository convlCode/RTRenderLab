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

    float vertices[] = {
           -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
           -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
           -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

           -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
           -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
           -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

           -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
           -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
           -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
           -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
           -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
           -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

           -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
           -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
           -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

           -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
           -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
           -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    core->glGenVertexArrays(1, &VAO);
    core->glGenBuffers(1, &VBO);

    core->glBindVertexArray(VAO);

    core->glBindBuffer(GL_ARRAY_BUFFER, VBO);
    core->glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    core->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), reinterpret_cast<void*>(0));
    core->glEnableVertexAttribArray(0);

    core->glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat),reinterpret_cast<void*>(3*sizeof(GLfloat)));
    core->glEnableVertexAttribArray(1);

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
    myShader->setInt("texture1",0);
    myShader->setInt("texture2",1);

    time.start();
    cubePositions = {
        QVector3D( 0.0f,  0.0f,  -1.0f),
        QVector3D( 2.0f,  5.0f, -15.0f),
        QVector3D(-1.5f, -2.2f, -2.5f),
        QVector3D(-3.8f, -2.0f, -12.3f),
        QVector3D( 2.4f, -0.4f, -3.5f),
        QVector3D(-1.7f,  3.0f, -7.5f),
        QVector3D( 1.3f, -2.0f, -2.5f),
        QVector3D( 1.5f,  2.0f, -2.5f),
        QVector3D( 1.5f,  0.2f, -1.5f),
        QVector3D(-1.3f,  1.0f, -1.5f)
    };
    QMatrix4x4 view,projection;
    //model.rotate(-55.0f,QVector3D(1.0f,0.0f,0.0f));
    view.translate(QVector3D(0.0f,0.0f,-3.0f));
    projection.perspective(45.0f,static_cast<float>(width())/static_cast<float>(height()),0.1f,100.0f);

    myShader->use();
    //myShader->setMat4("model",model);
    myShader->setMat4("view",view);
    myShader->setMat4("projection",projection);

    core->glEnable(GL_DEPTH_TEST);
}

void GLWidget::resizeGL(int w, int h)
{
    core->glViewport(0,0,w,h);
}

void GLWidget::paintGL()
{
    core->glClearColor(0.2f,0.3f,0.3f,1.0f);
    core->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    core->glActiveTexture(GL_TEXTURE0);
    texture1->bind();
    core->glActiveTexture(GL_TEXTURE1);
    texture2->bind();

    for(int i = 0;i<10;++i){
        QMatrix4x4 model;
        model.translate(cubePositions[i]);
        model.rotate(static_cast<float>(time.elapsed())/10.0f,cubePositions[i]);

        myShader->use();
        myShader->setMat4("model",model);
        core->glBindVertexArray(VAO);
        core->glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    update();
}
