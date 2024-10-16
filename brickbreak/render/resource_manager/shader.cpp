#include "../resource_manager.h"

#include <glad/glad.h>

#include <stdexcept>
#include <string>

namespace render
{
namespace resource_manager
{
namespace shader
{
  unsigned int compile(const char *source_vertex, const char *source_fragment)
  {
    int  success;
    char info_log[512];
    // vertex shader
    unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &source_vertex, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success)
    {
      glGetShaderInfoLog(vertex, 512, NULL, info_log);
      std::string error_message = "ERROR: vertex shader compilation failed: " + std::string(info_log) + "\n";
      throw std::runtime_error(error_message.c_str());
    }

    // fragment shader
    unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &source_fragment, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success)
    {
      glGetShaderInfoLog(fragment, 512, NULL, info_log);
      std::string error_message = "ERROR: fragment shader compilation failed: " + std::string(info_log) + "\n";
      throw std::runtime_error(error_message.c_str());
    }

    // shader program
    unsigned int program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success)
    {
      glGetProgramInfoLog(program, 512, NULL, info_log);
      std::string error_message = "ERROR: shader program linking failed: " + std::string(info_log) + "\n";
      throw std::runtime_error(error_message.c_str());
    }
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return program;
  }
}
}
}
