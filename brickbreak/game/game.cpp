#include "../game.h"
#include "../render.h"

static game::component::Block player;

namespace game
{
  void init()
  {
    game::level::init();

    // player
    // ---
    player =
    {
      glm::vec3(100.0f, 500.0f, 0.0f),
      glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
      glm::vec3(100.0f, 10.0f, 0.0f)
    };
    // ---
  }

  void render()
  {
    game::level::render();

    // player
    // ---
    render::shapes::quad(player.top_left, player.size, player.color);
    // ---
  }
}
