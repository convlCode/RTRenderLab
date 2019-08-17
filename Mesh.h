#ifndef MESH_H
#define MESH_H

#include <QOpenGLFunctions_3_3_Core>
#include <QVector>
#include <QVector3D>
#include <QString>
#include <QOpenGLTexture>
//#include "Texture2D.h"
#include <QOpenGLShaderProgram>

struct Vertex {
    // position
    QVector3D Position;
    // normal
    QVector3D Normal;
    // texCoords
    QVector3D TexCoords;
    // tangent
    //QVector3D Tangent;
    // bitangent
    //QVector3D Bitangent;
};

struct Texture {
    //unsigned int id;
    QString type;
    QString fileName;
    QSharedPointer<QOpenGLTexture> texture;
};

class Mesh
{
public:
    Mesh(QVector<Vertex> vertices,QVector<unsigned int> indices,QVector<Texture> textures);
    ~Mesh();

    QVector<Vertex> vertices;
    QVector<unsigned int> indices;
    QVector<Texture> textures;
    unsigned int VAO;
    unsigned int VBO, EBO;
    QOpenGLFunctions_3_3_Core* core;
    bool isInitialized;


    void draw(QOpenGLShaderProgram* shaderProgram);

private:
    void setupMesh(QOpenGLShaderProgram* shaderProgram);
};

#endif // MESH_H
