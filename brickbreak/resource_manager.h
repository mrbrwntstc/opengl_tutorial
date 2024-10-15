#ifndef __RENDER_H__
#define __RENDER_H__

#include <map>
#include <string>

#include <glad/glad.h>

namespace resource_manager
{
  extern std::map<std::string, unsigned int> shaders;
  void add_shader(const char* name, const char* source_vertex, const char* source_fragment);
namespace shader
{
  unsigned int compile(const char* source_vertex, const char* source_fragment);
  inline void use(unsigned int id) { glUseProgram(id); }
  namespace uniform
  {
    inline void set_vec4(unsigned int id, const char* name, const float* value) { glUniform4fv(glGetUniformLocation(id, name), 1, value); }
    inline void set_mat4(unsigned int id, const char* name, const float* value) { glUniformMatrix4fv(glGetUniformLocation(id, name), 1, GL_FALSE, value); }
  }
}
}

#endif // __RENDER_H__
