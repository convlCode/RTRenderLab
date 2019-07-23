#include "GLWidget.h"
#include <QImage>
#include <QKeyEvent>
#include "ResourceManager.h"

GLWidget::GLWidget(QWidget* parent,Qt::WindowFlags f)
    :QOpenGLWidget(parent, f)
{
    //this->grabKeyboard(); we can set the focusPolicy to get the keyboard.
}

GLWidget::~GLWidget()
{
    delete cube;
    delete camera;
    //texture->destroy();
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

    cube = new Cube();
    cube->init();

    plane = new Plane();
    plane->init();

    coordinate = new Coordinate();
    coordinate->init();

    core->glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat),reinterpret_cast<void*>(3*sizeof(GLfloat)));
    core->glEnableVertexAttribArray(1);

    ResourceManager::loadShader("coordinate", ":/shaders/coordinate.vs", ":/shaders/coordinate.fs");
    ResourceManager::loadShader("cube", ":/shaders/cube.vs", ":/shaders/cube.fs");
    ResourceManager::loadShader("plane", ":/shaders/plane.vs", ":/shaders/plane.fs");

    ResourceManager::loadTexture("brickwall", ":/textures/brickwall.jpg");
    ResourceManager::loadTexture("cementwall", ":/textures/cementwall.jpg");

    /***********  cube shader **************/
    QMatrix4x4 model;
    ResourceManager::getShader("cube").use().setMatrix4f("model", model);
    ResourceManager::getShader("cube").use().setInteger("ambientMap", 0);

    /***********  plane shader**************/
    model.setToIdentity();
    model.translate(0.0f, -0.8f, 0.0f);
    model.scale(2.0f);
    ResourceManager::getShader("plane").use().setMatrix4f("model", model);
    ResourceManager::getShader("plane").use().setInteger("ambientMap", 0);


    /***********  coordinate shader**************/
    model.setToIdentity();
    model.scale(20.0f);
    ResourceManager::getShader("coordinate").use().setMatrix4f("model", model);

    core->glEnable(GL_DEPTH_TEST);
    core->glClearColor(0.3f,0.3f,0.3f,1.0f);
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
    this->updateGL();

    ResourceManager::getShader("cube").use();
    core->glActiveTexture(GL_TEXTURE0);
    ResourceManager::getTexture("brickwall").bind();
    cube->draw(GL_TRUE);

    ResourceManager::getShader("plane").use();
    core->glActiveTexture(GL_TEXTURE0);
    ResourceManager::getTexture("cementwall").bind();
    plane->draw(GL_TRUE);

    ResourceManager::getShader("coordinate").use();
    coordinate->draw();

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

void GLWidget::updateGL(){
  if(this->isLineMode)
    core->glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  else
    core->glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  QMatrix4x4 projection, view;
  projection.perspective(camera->zoom, static_cast<GLfloat>(width()) / static_cast<GLfloat>(height()), 0.1f, 2000.f);
  view = camera->getViewMatrix();

  ResourceManager::getShader("cube").use().setMatrix4f("projection", projection);
  ResourceManager::getShader("cube").use().setMatrix4f("view", view);

  ResourceManager::getShader("plane").use().setMatrix4f("projection", projection);
  ResourceManager::getShader("plane").use().setMatrix4f("view", view);

  ResourceManager::getShader("coordinate").use().setMatrix4f("projection", projection);
  ResourceManager::getShader("coordinate").use().setMatrix4f("view", view);
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
