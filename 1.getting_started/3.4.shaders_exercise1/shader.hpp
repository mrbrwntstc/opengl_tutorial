#ifndef __SHADER_HPP__
#define __SHADER_HPP__

#include <glad/glad.h>

#include <stdlib.h>

class Shader
{
public: // fields
  unsigned int ID;
public: // methods
  Shader(const char *vertexPath, const char *fragmentPath);
  void use();
  // void setBool(const char* name, bool value) const;
  // void setInt(const char* name, int value) const;
  // void setFloat(const char* name, float value) const;
};

#endif // __SHADER_HPP__