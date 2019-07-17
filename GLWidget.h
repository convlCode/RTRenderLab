#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include "Shader.h"
#include <QOpenGLTexture>
#include <QTime>
#include <QVector>

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
};

#endif // GLWIDGET_H
