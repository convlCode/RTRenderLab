#include "Cube.h"

Cube::Cube(): VBO(0){
  core = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>();
}

Cube::~Cube(){
  if(VBO != 0)
    core->glDeleteBuffers(1, &VBO);
  core->glDeleteVertexArrays(1,&cubeVAO);
  core->glDeleteVertexArrays(1,&lightVAO);
}

void Cube::init(){
  float vertices[] = {
    // positions        // textures        // normals
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  1.0f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  1.0f,  0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  0.0f,  0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  0.0f,  0.0f,  1.0f,

    -0.5f,  0.5f,  0.5f,  1.0f,  0.0f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  1.0f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  1.0f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f,  0.0f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  1.0f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  1.0f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f,  1.0f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  1.0f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  1.0f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
  };
  core->glGenVertexArrays(1,&cubeVAO);
  core->glGenVertexArrays(1,&lightVAO);
  core->glGenBuffers(1, &VBO);

  core->glBindBuffer(GL_ARRAY_BUFFER, VBO);
  core->glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  core->glBindVertexArray(cubeVAO);
    core->glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8 * sizeof(float),reinterpret_cast<void*>(0));
    core->glEnableVertexAttribArray(0);
  core->glBindVertexArray(0);

  core->glBindVertexArray(lightVAO);
    core->glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8 * sizeof(float),reinterpret_cast<void*>(0));
    core->glEnableVertexAttribArray(0);
  core->glBindVertexArray(0);

  core->glDeleteBuffers(1,&VBO);
}
/*
void Cube::draw(GLboolean isTexture, GLboolean isNormal){
  core->glBindBuffer(GL_ARRAY_BUFFER, VBO);

  core->glEnableVertexAttribArray(0);

  core->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(0));
  if(isTexture){
    core->glEnableVertexAttribArray(1);
    core->glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(3*sizeof(float)));
  }
  if(isNormal){
    core->glEnableVertexAttribArray(2);
    core->glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(5*sizeof(float)));
  }

  core->glDrawArrays(GL_TRIANGLES, 0, 36);
}*/

void Cube::drawCube()
{
    core->glBindVertexArray(cubeVAO);
    core->glDrawArrays(GL_TRIANGLES,0,36);
}

void Cube::drawLight()
{
    core->glBindVertexArray(lightVAO);
    core->glDrawArrays(GL_TRIANGLES,0,36);
}
