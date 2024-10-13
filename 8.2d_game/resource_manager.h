#ifndef __RESOURCE_MANAGER_H__
#define __RESOURCE_MANAGER_H__

#include <map>
#include <string>

#include <glad/glad.h>

#include "texture.hpp"
#include "shader.hpp"

class ResourceManager
{
public: // fields
  static std::map<std::string, Shader> Shaders;
  static std::map<std::string, Texture2D> Textures;
public: // methods
  // create a new shader program from files
  static Shader LoadShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, std::string shader);
  // from ResourceManager::Shaders
  static Shader GetShader(std::string name);
  // create new texture from file
  static Texture2D LoadTexture(const char *file, bool alpha, std::string name);
  // from ResourceManager::Textures
  static Texture2D GetTexture(std::string name);
  // cleanup
  static void Clear();
private: // methods
  ResourceManager() {}
  static Shader loadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile);
  static Texture2D loadTextureFromFile(const char *file, bool alpha);
};

#endif // __RESOURCE_MANAGER_H__