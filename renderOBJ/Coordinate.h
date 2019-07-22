#ifndef COORDINATE_H
#define COORDINATE_H

#include <QOpenGLFunctions_3_3_Core>

class Coordinate{
public:
  Coordinate();
  ~Coordinate();
  void init();
  void draw();
private:
  QOpenGLFunctions_3_3_Core *core;
  GLuint VBO;
};

#endif // COORDINATE_H
