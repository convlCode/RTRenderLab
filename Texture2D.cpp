#include "Texture2D.h"

Texture2D::Texture2D():internalFormat(QOpenGLTexture::RGBFormat),
    wrap_s(QOpenGLTexture::Repeat), wrap_t(QOpenGLTexture::Repeat),
    filterMax(QOpenGLTexture::Linear),filterMin(QOpenGLTexture::Linear),texture(nullptr)
{

}

Texture2D::~Texture2D()
{
//    delete texture;
}

void Texture2D::generate(const QString &file)
{
  texture = new QOpenGLTexture(QOpenGLTexture::Target2D);
  texture->setFormat(internalFormat);
  texture->setData(QImage(file).mirrored(), QOpenGLTexture::GenerateMipMaps);

  texture->setWrapMode(QOpenGLTexture::DirectionS, wrap_s);//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  texture->setWrapMode(QOpenGLTexture::DirectionT, wrap_t);//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  texture->setMinificationFilter(filterMin);   //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  texture->setMagnificationFilter(filterMax);  //     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Texture2D::bind() const
{
  texture->bind();
}
