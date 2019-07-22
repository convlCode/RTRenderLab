#include "Coordinate.h"

Coordinate::Coordinate(): VBO(0){
  core = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>();
}

Coordinate::~Coordinate(){
  if(VBO != 0)
    core->glDeleteBuffers(1, &VBO);
}

void Coordinate::init(){

  float vertices[] = {
      // positions
      0.0f, 0.0f, 0.0f,
      1.0f, 0.0f, 0.0f,

      0.0f, 0.0f, 0.0f,
      0.0f, 1.0f, 0.0f,

      0.0f, 0.0f, 0.0f,
      0.0f, 0.0f, 1.0f
  };

  core->glGenBuffers(1, &VBO);

  core->glBindBuffer(GL_ARRAY_BUFFER, VBO);
  core->glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


}

void Coordinate::draw(){
  core->glEnableVertexAttribArray(0);
  core->glBindBuffer(GL_ARRAY_BUFFER, VBO);
  core->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), reinterpret_cast<void*>(0));

  core->glDrawArrays(GL_LINES, 0, 6);
}
