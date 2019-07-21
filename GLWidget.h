#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include "Shader.h"
#include <QOpenGLTexture>
#include <QTime>
#include <QVector>
#include <QVector3D>
#include "Camera.h"

class GLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    GLWidget(QWidget* parent = nullptr,Qt::WindowFlags f =Qt::WindowFlags());
    ~GLWidget();

    GLuint a;
protected:
    virtual void initializeGL();
    virtual void resizeGL(int w,int h);
    virtual void paintGL();

    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
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

    Camera* camera;

    GLfloat   deltaTime;
    GLfloat   lastFrame;

    bool    isFirstMouse;
    bool    isLeftMousePress;

    float   lastX;
    float   lastY;
};

#endif // GLWIDGET_H
