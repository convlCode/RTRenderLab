﻿#include "GLWidget.h"
#include <QImage>
#include <QKeyEvent>
#include <QDir>
#include "ResourceManager.h"

GLWidget::GLWidget(QWidget* parent,Qt::WindowFlags f)
    :QOpenGLWidget(parent, f),timeCount{0.0f}
{
    //this->grabKeyboard(); we can set the focusPolicy to get the keyboard.
    cubePositions = {
        QVector3D( 0.0f,  0.0f,  0.0f),
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
}

GLWidget::~GLWidget()
{
    //delete cube;
    //delete plane;
    //delete coordinate;
    delete camera;
    //texture->destroy();
    //ResourceManager::clear();
}

void GLWidget::changeObjModel(const QString &fileName)
{
    if(fileName != ""){
        if(camera != nullptr){
            delete camera;
            camera = nullptr;
        }
        camera = new Camera(QVector3D(0.0f,0.0f,3.0f));
        if(fileName != "")
            pmodel->updateModel(fileName);
    }
}

void GLWidget::initializeGL()
{
    core = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>();

    isOpenLighting = GL_TRUE;
    isLineMode = GL_FALSE;
    modelScaling = 0.15f;

    deltaTime = 0.0f;
    lastFrame = 0.0f;

    isFirstMouse = true;
    isLeftMousePress = false;
    lastX = width() / 2.0f;
    lastY = height() / 2.0f;

    time.start();

    camera = new Camera(QVector3D(0.0f,0.0f,3.0f));
    qDebug()<<QDir::currentPath();
    //pmodel = new Model("./objects/nanosuit/nanosuit.obj");

    cube = new Cube();
    cube->init();

    plane = new Plane();
    plane->init();

    ResourceManager::loadShader("cube_dtest",":/shaders/cube_dtest.vs",":/shaders/cube_dtest.fs");
    ResourceManager::loadShader("plane",":/shaders/plane.vs",":/shaders/plane.fs");
    //ResourceManager::loadShader("coordinate","","");

    ResourceManager::loadTexture("marble",":/textures/marble.jpg");
    ResourceManager::loadTexture("metal",":/textures/metal.png");

    ResourceManager::getShader("cube_dtest").use().setInteger("ambientMap", 0);

    QMatrix4x4 model;
    model.translate(0.0f, -0.5f, 0.0f);
    model.scale(10.0f);
    ResourceManager::getShader("plane").use().setMatrix4f("model", model);
    ResourceManager::getShader("plane").use().setInteger("ambientMap", 0);

    core->glEnable(GL_DEPTH_TEST);
    core->glDepthFunc(GL_ALWAYS);
    //core->glClearColor(0.05f,0.05f,0.05f,1.0f);
    core->glClearColor(0.3f,0.3f,0.3f,1.0f);
    core->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLWidget::resizeGL(int w, int h)
{
    core->glViewport(0,0,w,h);
}

void GLWidget::paintGL()
{
    core->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    GLfloat currentFrame = static_cast<GLfloat>(time.elapsed()) / 100.0f;
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;


    camera->processInput(deltaTime); //it may change the camera's vectors.
    this->updateGL(deltaTime); //it will compute new view and projection matrix after changing of camera.

    QMatrix4x4 model;
    model.translate(-1.0f, 0.0f, -1.0f);
    ResourceManager::getShader("cube_dtest").use().setMatrix4f("model", model);
    core->glActiveTexture(GL_TEXTURE0);
    ResourceManager::getTexture("marble").bind();
    cube->drawCube();

    model.setToIdentity();
    model.translate(1.0f, 0.0f, 0.0f);
    ResourceManager::getShader("cube_dtest").use().setMatrix4f("model",model);
    cube->drawCube();

    ResourceManager::getShader("plane").use();
    core->glActiveTexture(GL_TEXTURE0);
    ResourceManager::getTexture("metal").bind();
    plane->draw(GL_TRUE);
    //ResourceManager::getShader("modelLoad").use();
    //pmodel->Draw(ResourceManager::getShader("modelLoad").shaderProgram);

    update();
}
/*
void GLWidget::processInput(GLfloat dt){
  if (keys[Qt::Key_W])
    camera->processKeyboard(FORWARD, dt);
  if (keys[Qt::Key_S])
    camera->processKeyboard(BACKWARD, dt);
  if (keys[Qt::Key_A])
    camera->processKeyboard(LEFT, dt);
  if (keys[Qt::Key_D])
    camera->processKeyboard(RIGHT, dt);
  if (keys[Qt::Key_E])
    camera->processKeyboard(UP, dt);
  if (keys[Qt::Key_Q])
    camera->processKeyboard(DOWN, dt);

}*/

void GLWidget::updateGL(GLfloat dt){
  if(this->isLineMode)
    core->glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  else
    core->glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  //QMatrix4x4 projection, view;
  QMatrix4x4 projection, view;
  projection.perspective(camera->zoom, static_cast<GLfloat>(width()) / static_cast<GLfloat>(height()), 0.1f, 200.f);
  view = camera->getViewMatrix(); //it due to the camera->position,and camera->position changed when press key.

  ResourceManager::getShader("cube_dtest").use().setMatrix4f("projection",projection);
  ResourceManager::getShader("cube_dtest").use().setMatrix4f("view",view);

  ResourceManager::getShader("plane").use().setMatrix4f("projection", projection);
  ResourceManager::getShader("plane").use().setMatrix4f("view", view);
}

void GLWidget::keyPressEvent(QKeyEvent *event)
{
    GLint key = event->key();
    if(key >= 0 && key <= 1024)
      camera->keys[key] = GL_TRUE;
}

void GLWidget::keyReleaseEvent(QKeyEvent *event)
{
    GLint key = event->key();
    if(key >= 0 && key <= 1024)
        camera->keys[key] = GL_FALSE;
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    GLint xpos = event->pos().x();
    GLint ypos = event->pos().y();

    if(isLeftMousePress){
        if(isFirstMouse){
            lastX = xpos;
            lastY = ypos;
            isFirstMouse = GL_FALSE;
        }

        GLfloat xoffset = xpos - lastX;
        GLfloat yoffset = lastY - ypos;
        lastX = xpos;
        lastY = ypos;
        camera->processMouseMovement(xoffset,yoffset);
    }
}

void GLWidget::wheelEvent(QWheelEvent *event)
{
   QPoint offset = event->angleDelta();
   camera->processMouseScroll(offset.y()/20.0f);
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        isLeftMousePress = GL_TRUE;
    }
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        isLeftMousePress = GL_FALSE;
        isFirstMouse = GL_TRUE;
    }
}
