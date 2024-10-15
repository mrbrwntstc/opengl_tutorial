#include "../resource_manager.h"

#include <glad/glad.h>

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
      fprintf(stderr, "ERROR: vertex shader compilation failed: %s\n", info_log);
      return -1;
    }

    // fragment shader
    unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &source_fragment, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success)
    {
      glGetShaderInfoLog(fragment, 512, NULL, info_log);
      fprintf(stderr, "ERROR: fragment shader compilation failed: %s\n", info_log);
      return -1;
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
      fprintf(stderr, "ERROR: shader program linking failed: %s\n", info_log);
      return -1;
    }
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return program;
  }
}
}
}
