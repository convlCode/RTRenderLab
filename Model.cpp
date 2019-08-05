#include "Model.h"

Model::Model(QString const &path, bool gamma)
    : gammaCorrection{gamma}
{
    loadModel(path);
}

void Model::Draw(Shader shader)
{
    for(int i=0;i < meshes.size();++i){
        meshes[i].draw(shader);
    }
}

void Model::loadModel(const QString &path)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path.toStdString(),aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    directory = path.mid(0,path.lastIndexOf('/'));
    processNode(scene->mRootNode,scene);
}

void Model::processNode(aiNode* node,const aiScene* scene)
{

}
