#include "Model.h"

static QSharedPointer<QOpenGLTexture> textureFromFile(const QString &path, const QString &directory)
{
    QString fileName = directory + '/' + path;

    QImage image(fileName);
    QSharedPointer<QOpenGLTexture> texture(new QOpenGLTexture(QOpenGLTexture::Target2D));

    texture->setFormat(QOpenGLTexture::RGBFormat);
    texture->setData(image.mirrored(),QOpenGLTexture::GenerateMipMaps);

    texture->setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::Repeat);
    texture->setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::Repeat);
    texture->setMinificationFilter(QOpenGLTexture::Linear);
    texture->setMagnificationFilter(QOpenGLTexture::Linear);
    return texture;
}

Model::Model(QString const &path, bool gamma)
    : gammaCorrection{gamma}
{
    loadModel(path);
}

void Model::Draw(QOpenGLShaderProgram* shaderProgram)
{
    for(int i=0;i < meshes.size();++i){
        meshes[i].draw(shaderProgram);
    }
}

void Model::loadModel(const QString &path)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path.toStdString(),aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    //directory = path.mid(0,path.lastIndexOf('/'));
    directory = path.left(path.lastIndexOf("/"));
    processNode(scene->mRootNode,scene);
}

void Model::processNode(aiNode* node,const aiScene* scene)
{
    for (unsigned int i = 0;i<node->mNumMeshes;i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh,scene));
    }
    for(unsigned int i=0;i<node->mNumChildren;i++){
        processNode(node->mChildren[i],scene);
    }
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
    // data to fill
    QVector<Vertex> vertices;
    QVector<unsigned int> indices;
    QVector<Texture> textures;

    // Walk through each of the mesh's vertices
    for(unsigned int i = 0; i < mesh->mNumVertices; i++){
        Vertex vertex;
        QVector3D vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
        // positions
        vector.setX(mesh->mVertices[i].x);
        vector.setY(mesh->mVertices[i].y);
        vector.setZ(mesh->mVertices[i].z);
        vertex.Position = vector;
        // normals
        vector.setX(mesh->mNormals[i].x);
        vector.setY(mesh->mNormals[i].y);
        vector.setZ(mesh->mNormals[i].z);
        vertex.Normal = vector;
        // texture coordinates
        if(mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            QVector2D vec;
            // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            vec.setX(mesh->mTextureCoords[0][i].x);
            vec.setY(mesh->mTextureCoords[0][i].y);
            vertex.TexCoords = vec;
        }
        else
            vertex.TexCoords = QVector2D(0.0f, 0.0f);

        // tangent
        //vector.setX(mesh->mTangents[i].x);
        //vector.setY(mesh->mTangents[i].y);
        //vector.setZ(mesh->mTangents[i].z);
        //vertex.Tangent = vector;
        // bitangent
        //vector.setX(mesh->mBitangents[i].x);
        //vector.setY(mesh->mBitangents[i].y);
        //vector.setZ(mesh->mBitangents[i].z);
        //vertex.Bitangent = vector;

        vertices.push_back(vertex);
    }
    // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for(unsigned int i = 0; i < mesh->mNumFaces; i++){
        aiFace face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    // process materials
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
    // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER.
    // Same applies to other texture as the following list summarizes:
    // diffuse: texture_diffuseN
    // specular: texture_specularN
    // normal: texture_normalN

    // 1. diffuse maps
    QVector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.append(diffuseMaps);
    //textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    // 2. specular maps
    QVector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.append(specularMaps);
    //textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    // 3. normal maps
    QVector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    textures.append(normalMaps);
    //textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    // 4. height maps
    QVector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
    textures.append(heightMaps);
    //textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    // return a mesh object created from the extracted mesh data
    return Mesh(vertices, indices, textures);
}

QVector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, QString typeName)
{
    QVector<Texture> textures;
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++){
        aiString str;
        mat->GetTexture(type, i, &str);
        // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
        bool skip = false;
        QString path(str.C_Str());
        path.right(path.length()-path.lastIndexOf('\\')-1);
        for(int j = 0; j < textures_loaded.size(); j++){
            if(textures_loaded[j].fileName == path){
                textures.push_back(textures_loaded[j]);
                skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization
                break;
            }
        }
        if(!skip){   // if texture hasn't been loaded already, load it
            Texture texture;
            texture.texture = textureFromFile(path, this->directory);
            texture.type = typeName;
            texture.fileName = path;

            textures.push_back(texture);
            textures_loaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
        }
    }

    return textures;
}
