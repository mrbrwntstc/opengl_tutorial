#ifndef __BRICKBREAK_GAME_H__
#define __BRICKBREAK_GAME_H__

#include <glm/glm.hpp>

#include <array>

namespace game
{
  void init();
  void process_input();
  void render();
  void cleanup();
namespace frame
{
  void start();
  void end();
}

namespace component
{
  struct Block
  {
    glm::vec3 top_left;
    glm::vec4 color;
    glm::vec3 size;
  };

  struct Ball
  {
    glm::vec3 center;
    float radius;
    glm::vec4 color;
  };
}

namespace level
{
  void init();
  void render();
}
}

#endif // __BRICKBREAK_GAME_H__
