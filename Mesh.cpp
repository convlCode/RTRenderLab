#include "Mesh.h"
#include "ResourceManager.h"

Mesh::Mesh(QVector<Vertex> vertices,QVector<unsigned int> indices,QVector<Texture> textures)
    :isInitialized(false)
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;
    core = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>();
}

Mesh::~Mesh()
{
    core->glDeleteBuffers(1,&VAO);
    core->glDeleteBuffers(1,&VBO);
    core->glDeleteBuffers(1,&EBO);
}

void Mesh::draw(QOpenGLShaderProgram* shaderProgram)
{
    if(!isInitialized){
        setupMesh(shaderProgram);
        isInitialized = true;
    }

    // bind appropriate textures
    unsigned int diffuseNr  = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr   = 1;
    unsigned int heightNr   = 1;

    for(int i = 0; i < textures.size(); i++)
    {
        //core->glActiveTexture(GL_TEXTURE0 + static_cast<unsigned int>(i)); // active proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        QString number;
        QString name = textures[i].type;
        if(name == "texture_diffuse")
            number = QString::number(diffuseNr++);
        else if(name == "texture_specular")
            number = QString::number(specularNr++); // transfer unsigned int to stream
        else if(name == "texture_normal")
            number = QString::number(normalNr++); // transfer unsigned int to stream
         else if(name == "texture_height")
            number = QString::number(heightNr++); // transfer unsigned int to stream

                                                 // now set the sampler to the correct texture unit
        //core->glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()), i);
        if(name == "texture_diffuse"){
            QString uniformName = QString(name + number);
            shaderProgram->setUniformValue(QString(name + number).toLocal8Bit().constData(), i);
            //ResourceManager::getShader("modelLoad").use().setInteger(uniformName,i);
            // and finally bind the texture
            textures[i].texture->bind(static_cast<unsigned int>(i));
        }
    }

    // draw mesh
    core->glBindVertexArray(VAO);
    core->glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, reinterpret_cast<void*>(0));
    core->glBindVertexArray(0);

    // always good practice to set everything back to defaults once configured.
    //core->glActiveTexture(GL_TEXTURE0);
}

void Mesh::setupMesh(QOpenGLShaderProgram* shaderProgram)
{
    // create buffers/arrays
    core->glGenVertexArrays(1, &VAO);
    core->glGenBuffers(1, &VBO);
    core->glGenBuffers(1, &EBO);

    core->glBindVertexArray(VAO);
    // load data into vertex buffers
    core->glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // A great thing about structs is that their memory layout is sequential for all its items.
    // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
    // again translates to 3/2 floats which translates to a byte array.

    core->glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    core->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    core->glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()  * static_cast<int>(sizeof(unsigned int)) , &indices[0], GL_STATIC_DRAW);

    // set the vertex attribute pointers
    // vertex Positions
    core->glEnableVertexAttribArray(0);
    core->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(0));
    // vertex normals
    core->glEnableVertexAttribArray(1);
    core->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, Normal)));
    // vertex texture coords
    core->glEnableVertexAttribArray(2);
    core->glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, TexCoords)));
    // vertex tangent
    //core->glEnableVertexAttribArray(3);
    //core->glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, Tangent)));
    // vertex bitangent
    //core->glEnableVertexAttribArray(4);
    //core->glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, Bitangent)));

    core->glBindVertexArray(0);
}
