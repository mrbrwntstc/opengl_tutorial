#ifndef __SHADER_H__
#define __SHADER_H__

#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public: // fields
  unsigned int ID;
public: // methods
  Shader() {}
  Shader& Use();
  ~Shader();
  void Compile(const char* vertex_source, const char* fragment_source, const char* geometry_source = nullptr);
  void SetFloat(const char* name, float value, bool useShader = false);
  void SetInteger(const char* name, int value, bool useShader = false);
  void SetVector2f(const char* name, const glm::vec2& vector, bool useShader = false);
  void SetVector3f(const char* name, const glm::vec3& vector, bool useShader = false);
  void SetVector4f(const char* name, const glm::vec4& vector, bool useShader = false);
  void SetMatrix4(const char* name, const glm::mat4& matrix, bool useShader = false);
private: // methods
  void checkCompileErrors(unsigned int object, std::string type);
};

#endif // __SHADER_H__