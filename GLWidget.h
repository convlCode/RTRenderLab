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
#include "renderOBJ/Cube.h"
#include "renderOBJ/Plane.h"
#include "renderOBJ/Coordinate.h"

class GLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    GLWidget(QWidget* parent = nullptr,Qt::WindowFlags f =Qt::WindowFlags());
    ~GLWidget();

    //GLboolean keys[1024];
    GLboolean isOpenLighting;
    GLboolean isLineMode;

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

    //void processInput(GLfloat dt);
    void updateGL(GLfloat dt);

    QOpenGLFunctions_3_3_Core* core;

    QTime time;
    GLfloat timeCount;

    Camera* camera;

    GLfloat   deltaTime;
    GLfloat   lastFrame;

    bool    isFirstMouse;
    bool    isLeftMousePress;

    float   lastX;
    float   lastY;

    Coordinate *coordinate;
    Cube *cube;
    Plane *plane;

    QVector<QVector3D> cubePositions;
};

#endif // GLWIDGET_H
