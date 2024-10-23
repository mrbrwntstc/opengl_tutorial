#ifndef __BRICKBREAK_GAME_H__
#define __BRICKBREAK_GAME_H__

#include "render.h"
#include "input.h"
#include "time.h"

#include <glm/glm.hpp>

#include <array>

namespace game
{
  void init();
  void update();
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
    glm::vec3 velocity;
    float radius;
    glm::vec4 color;
  };
}

namespace level
{
  void init();
  void render();
  void check_collision(game::component::Ball &ball);
}
}

#endif // __BRICKBREAK_GAME_H__
