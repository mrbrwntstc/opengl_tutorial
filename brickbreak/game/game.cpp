#include "../game.h"
#include "../render.h"

static game::component::Block player;
static game::component::Ball ball;

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

    // ball
    // ---
    float ball_x = player.top_left.x + player.size.x / 2;
    float ball_radius = 10.0f;
    float ball_y = player.top_left.y - ball_radius;
    ball = {
      glm::vec3(ball_x, ball_y, 0.0f),
      ball_radius,
      glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)
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

    // ball
    // ---
    render::shapes::circle(ball.center, ball.radius, ball.color);
    // ---
  }
}
