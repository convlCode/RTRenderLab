#include "GLWidget.h"
#include <QImage>
#include <QKeyEvent>
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

void GLWidget::initializeGL()
{
    core = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>();
    isOpenLighting = GL_TRUE;
    isLineMode = GL_FALSE;

    deltaTime = 0.0f;
    lastFrame = 0.0f;

    isFirstMouse = true;
    isLeftMousePress = false;
    lastX = width() / 2.0f;
    lastY = height() / 2.0f;

    time.start();

    camera = new Camera(QVector3D(0.0f,0.0f,3.0f));

    pmodel = new Model("D:/Qt/qtProjects/RTRenderLab/nanosuit/nanosuit.obj");

    core->glBindBuffer(GL_ARRAY_BUFFER,0);
    core->glBindVertexArray(0);

    //program->addShaderFromSourceFile(QOpenGLShader::Vertex,"D:/Qt/qtProjects/RTRenderLab/shaders/modelLoad.vs");
    //program->addShaderFromSourceFile(QOpenGLShader::Fragment,"D:/Qt/qtProjects/RTRenderLab/shaders/modelLoad.fs");
    //program->link();
    ResourceManager::loadShader("modelLoad",":/shaders/modelLoad.vs",":/shaders/modelLoad.fs");

    core->glEnable(GL_DEPTH_TEST);
    core->glClearColor(0.2f,0.3f,0.3f,1.0f);
    core->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLWidget::resizeGL(int w, int h)
{
    core->glViewport(0,0,w,h);
}

void GLWidget::paintGL()
{
    GLfloat currentFrame = static_cast<GLfloat>(time.elapsed()) / 100.0f;
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;


    camera->processInput(deltaTime);
    this->updateGL(deltaTime);


    ResourceManager::getShader("modelLoad").use();

    pmodel->Draw(ResourceManager::getShader("modelLoad").shaderProgram);

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
  QMatrix4x4 projection, view, model;
  projection.perspective(camera->zoom, static_cast<GLfloat>(width()) / static_cast<GLfloat>(height()), 0.1f, 200.f);
  view = camera->getViewMatrix();
  model.scale(0.015f, 0.015f, 0.015f);
  ResourceManager::getShader("modelLoad").use().setMatrix4f("projection",projection);
  ResourceManager::getShader("modelLoad").use().setMatrix4f("projection",view);
  ResourceManager::getShader("modelLoad").use().setMatrix4f("projection",model);
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
