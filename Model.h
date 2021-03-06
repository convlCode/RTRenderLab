﻿#ifndef MODEL_H
#define MODEL_H

#include <QOpenGLFunctions_3_3_Core>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <QVector>
#include <QString>
#include "Mesh.h"

class Model
{
public:
    Model(QString const &path, bool gamma = false);
    ~Model();
    void Draw(QOpenGLShaderProgram* shaderProgram);

    bool initFromScene(const aiScene* pscene,const QString &path);
    Mesh initMesh(const aiScene* pscene,const aiMesh* pmesh);

    void updateModel(QString const &path);

    QVector<Texture> textures_loaded;
    QVector<Mesh> meshes;
    QString directory;
    bool gammaCorrection;

private:
    void loadModel(QString const& path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh,const aiScene* scene);
    QVector<Texture> loadMaterialTextures(aiMaterial* mat,aiTextureType type,QString typeName);

    QOpenGLFunctions_3_3_Core *core;
};

#endif // MODEL_H
