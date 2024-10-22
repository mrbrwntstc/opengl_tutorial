#ifndef __BRICKBREAK_GAME_H__
#define __BRICKBREAK_GAME_H__

#include <glm/glm.hpp>

#include <array>

namespace game
{
  void init();

namespace component
{
  struct Block
  {
    glm::vec3 top_left;
    glm::vec4 color;
    glm::vec3 size;
  };
}

namespace level
{
  void init();
  void render();
}
}

#endif // __BRICKBREAK_GAME_H__
