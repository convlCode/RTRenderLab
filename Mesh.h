#ifndef MESH_H
#define MESH_H

#include <QOpenGLFunctions_3_3_Core>
#include <QVector>
#include <QVector3D>
#include <QString>
#include "Texture2D.h"
#include <Shader.h>

struct Vertex {
    // position
    QVector3D Position;
    // normal
    QVector3D Normal;
    // texCoords
    QVector3D TexCoords;
    // tangent
    QVector3D Tangent;
    // bitangent
    QVector3D Bitangent;
};

struct Texture {
    unsigned int id;
    QString type;
    QString path;
};

class Mesh
{
public:
    QVector<Vertex> vertices;
    QVector<unsigned int> indices;
    QVector<Texture> textures;
    unsigned int VAO;
    QOpenGLFunctions_3_3_Core* core;

    Mesh(QVector<Vertex> vertices,QVector<unsigned int> indices,QVector<Texture> textures);

    void draw(Shader shader);

private:
    unsigned int VBO, EBO;
    void setupMesh();
};

#endif // MESH_H
