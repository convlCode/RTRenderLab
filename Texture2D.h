#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include <QOpenGLTexture>

class Texture2D
{
    friend class ResourceManager;
public:
    Texture2D();
    ~Texture2D();

    void generate(const QString& file);
    void bind() const;

    QOpenGLTexture::TextureFormat internalFormat;
    QOpenGLTexture::WrapMode wrap_s;
    QOpenGLTexture::WrapMode wrap_t;
    QOpenGLTexture::Filter filterMax;
    QOpenGLTexture::Filter filterMin;

private:
    QOpenGLTexture* texture;
};

#endif // TEXTURE2D_H
