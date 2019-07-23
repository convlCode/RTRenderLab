#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <map>
#include <QString>

#include "Shader.h"
#include "Texture2D.h"


class ResourceManager
{
public:
  static std::map<QString, Shader> map_Shaders;
  static std::map<QString, Texture2D> map_Textures;

  static Shader loadShader(const QString& name, const QString& vShaderFile,
                           const QString& fShaderFile, const QString& gShaderfile = nullptr);
  static Shader getShader(const QString&  name);
  static Texture2D loadTexture(const QString&  name, const QString& file, GLboolean alpha = false);
  static Texture2D getTexture(const QString&  name);
  static void clear();

private:
  ResourceManager(){}

};

#endif // RESOURCEMANAGER_H
