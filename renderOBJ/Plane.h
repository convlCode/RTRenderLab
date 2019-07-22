#ifndef PLANE_H
#define PLANE_H

#include <QOpenGLFunctions_3_3_Core>

class Plane{
public:
  Plane();
  ~Plane();
  void init();
  void draw(GLboolean isTexture = GL_FALSE,GLboolean isNormal = GL_FALSE);
private:
  QOpenGLFunctions_3_3_Core *core;
  GLuint VBO;
};

#endif // PLANE_H
