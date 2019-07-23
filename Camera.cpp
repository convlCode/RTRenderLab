#include "Camera.h"
#include <QDebug>
QMatrix4x4 Camera::getViewMatrix()
{
  QMatrix4x4 view;
  view.lookAt(this->position, this->position + this->front, this->up);
  return view;
}

void Camera::processKeyboard(Camera_Movement direction, GLfloat deltaTime)
{
  //qDebug() << "in  processkeyboard dt: " << deltaTime <<endl;
  GLfloat velocity = this->movementSpeed * deltaTime;
  if (direction == FORWARD)
    this->position += this->front * velocity;
  if (direction == BACKWARD)
    this->position -= this->front * velocity;
  if (direction == LEFT)
    this->position -= this->right * velocity;
  if (direction == RIGHT)
    this->position += this->right * velocity;
  if (direction == UP)
    this->position += this->worldUp * velocity;
  if (direction == DOWN)
    this->position -= this->worldUp * velocity;
}

void Camera::processMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constraintPitch)
{
  xoffset *= this->mouseSensitivity;
  yoffset *= this->mouseSensitivity;

  this->yaw += xoffset;
  this->picth += yoffset;

  if (constraintPitch) {
    if (this->picth > 89.0f)
      this->picth = 89.0f;
    if (this->picth < -89.0f)
      this->picth = -89.0f;
  }

  this->updateCameraVectors();
}

void Camera::processMouseScroll(GLfloat yoffset)
{
  if (this->zoom >= 1.0f && this->zoom <= 45.0f)
    this->zoom -= yoffset;
  if (this->zoom > 45.0f)
    this->zoom = 45.0f;
  if (this->zoom < 1.0f)
      this->zoom = 1.0f;
}

void Camera::processInput(GLfloat dt)
{
    if (this->keys[Qt::Key_W])
      processKeyboard(FORWARD, dt);
    if (this->keys[Qt::Key_S])
      processKeyboard(BACKWARD, dt);
    if (this->keys[Qt::Key_A])
      processKeyboard(LEFT, dt);
    if (this->keys[Qt::Key_D])
      processKeyboard(RIGHT, dt);
    if (this->keys[Qt::Key_E])
      processKeyboard(UP, dt);
    if (this->keys[Qt::Key_Q])
      processKeyboard(DOWN, dt);
}

void Camera::updateCameraVectors()
{
  QVector3D front3(cos(this->yaw) * cos(this->picth), sin(this->picth), sin(this->yaw) * cos(this->picth));
  this->front = front3.normalized();
  this->right = QVector3D::crossProduct(this->front, this->worldUp).normalized();
  this->up = QVector3D::crossProduct(this->right, this->front).normalized();
}
