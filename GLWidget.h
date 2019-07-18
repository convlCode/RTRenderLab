#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include "Shader.h"
#include <QOpenGLTexture>
#include <QTime>
#include <QVector>
#include <QVector3D>

class GLWidget : public QOpenGLWidget
{
public:
    GLWidget(QWidget* parent = nullptr,Qt::WindowFlags f =Qt::WindowFlags());
    ~GLWidget();

    GLuint a;
protected:
    virtual void initializeGL();
    virtual void resizeGL(int w,int h);
    virtual void paintGL();

    void keyPressEvent(QKeyEvent* event);

private:
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
    Shader* myShader;
    QOpenGLFunctions_3_3_Core* core;

    QOpenGLTexture* texture1;
    QOpenGLTexture* texture2;

    QTime time;
    QVector<QVector3D> cubePositions;

    QVector3D cameraPos;
    QVector3D cameraFront;
    QVector3D cameraUp;
    GLfloat   deltaTime;
    GLfloat   lastFrame;
};

#endif // GLWIDGET_H
