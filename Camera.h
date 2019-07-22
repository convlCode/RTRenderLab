#ifndef CAMERA_H
#define CAMERA_H


#include <QVector3D>
#include <QMatrix4x4>
#include <QKeyEvent>
#include <QOpenGLShader>
#include <QDebug>


enum Camera_Movement {
  FORWARD,
  BACKWARD,
  LEFT,
  RIGHT,
  UP,
  DOWN
};

const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 1.0f;
const GLfloat SENSITIVITY = 0.01f;
const GLfloat ZOOM = 45.0f;

class Camera {
public:
    Camera(QVector3D position = QVector3D(0.0f, 0.0f, 0.0f), QVector3D up = QVector3D(0.0f, 1.0f, 0.0f),
    GLfloat yaw = YAW, GLfloat pitch = PITCH)
        : front(QVector3D(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM)
    {

        this->position = position;
        this->worldUp = up;
        this->yaw = yaw;
        this->picth = pitch;
        this->updateCameraVectors();

        for(GLuint i = 0; i != 1024; ++i)
            keys[i] = GL_FALSE;
    }

    QMatrix4x4 getViewMatrix();
    void processMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constraintPitch = true);
    void processMouseScroll(GLfloat yoffset);
    void processKeyboard(Camera_Movement direction, GLfloat deltaTime);

    QVector3D position;
    QVector3D worldUp;
    QVector3D front;

    QVector3D up;
    QVector3D right;

    //Eular Angles
    GLfloat picth;
    GLfloat yaw;

    //Camera options
    GLfloat movementSpeed;
    GLfloat mouseSensitivity;
    GLfloat zoom;

    GLboolean keys[1024];
private:
    void updateCameraVectors();

};

#endif // CAMERA_H
