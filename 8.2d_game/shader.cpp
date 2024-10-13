#include <iostream>

#include "shader.hpp"

Shader& Shader::Use() {
  glUseProgram(ID);
  return *this;
}

void Shader::Compile(const char* vertex_source, const char* fragment_source, const char* geometry_source) {
  unsigned int svertex, sfragment, gshader;
  // vertex
  svertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(svertex, 1, &vertex_source, NULL);
  glCompileShader(svertex);
  checkCompileErrors(svertex, "VERTEX");
  // fragment
  sfragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(sfragment, 1, &fragment_source, NULL);
  glCompileShader(sfragment);
  checkCompileErrors(sfragment, "FRAGMENT");
  if (geometry_source != nullptr) {
    gshader = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(gshader, 1, &geometry_source, NULL);
    glCompileShader(gshader);
    checkCompileErrors(gshader, "GEOMETRY");
  }
  // shader program
  ID = glCreateProgram();
  glAttachShader(ID, svertex);
  glAttachShader(ID, sfragment);
  if (geometry_source != nullptr) {
    glAttachShader(ID, gshader);
  }
  glLinkProgram(ID);
  checkCompileErrors(ID, "PROGRAM");
  // delete the shaders as they're linked into our program now and no longer necessary
  glDeleteShader(svertex);
  glDeleteShader(sfragment);
  if (geometry_source != nullptr) {
    glDeleteShader(gshader);
  }
}

void Shader::checkCompileErrors(unsigned int object, std::string type) {
  int success;
  char infoLog[1024];
  if (type != "PROGRAM") {
    glGetShaderiv(object, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(object, 1024, NULL, infoLog);
      std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
    }
  }
  else {
    glGetProgramiv(object, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(object, 1024, NULL, infoLog);
      std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
    }
  }
}

Shader::~Shader() {
  glDeleteProgram(ID);
}

void Shader::SetFloat(const char* name, float value, bool useShader) {
  if (useShader)
    this->Use();
  glUniform1f(glGetUniformLocation(ID, name), value);
}

void Shader::SetInteger(const char* name, int value, bool useShader) {
  if (useShader)
    this->Use();
  glUniform1i(glGetUniformLocation(ID, name), value);
}

void Shader::SetVector2f(const char* name, const glm::vec2& value, bool useShader) {
  if (useShader)
    this->Use();
  glUniform2f(glGetUniformLocation(ID, name), value.x, value.y);
}

void Shader::SetVector3f(const char* name, const glm::vec3& value, bool useShader) {
  if (useShader)
    this->Use();
  glUniform3f(glGetUniformLocation(ID, name), value.x, value.y, value.z);
}

void Shader::SetVector4f(const char* name, const glm::vec4& value, bool useShader) {
  if (useShader)
    this->Use();
  glUniform4f(glGetUniformLocation(ID, name), value.x, value.y, value.z, value.w);
}

void Shader::SetMatrix4(const char* name, const glm::mat4& matrix, bool useShader) {
  if (useShader)
    this->Use();
  glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(matrix));
}
