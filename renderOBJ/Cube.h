#ifndef CUBE_H
#define CUBE_H

#include <QOpenGLFunctions_3_3_Core>

class Cube{
public:
  Cube();
  ~Cube();
  void init();
  void draw(GLboolean isTexture = GL_FALSE,GLboolean isNormal = GL_FALSE);
private:
  QOpenGLFunctions_3_3_Core *core;
  GLuint VBO;
};

#endif // CUBE_H
