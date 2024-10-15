#include "../resource_manager.h"

namespace resource_manager
{
  std::map<std::string, unsigned int> shaders;

  void add_shader(const char* name, const char* source_vertex, const char* source_fragment)
  {
    shaders[name] = shader::compile(source_vertex, source_fragment);
  }
}
