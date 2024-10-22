#include "../game.h"

static game::component::Block player;
static game::component::Ball ball;

static const unsigned int width_window = 800;
static const unsigned int height_window = 600;

static enum GameState
{
  Start,
  Play
};

static GameState game_state = Start;

namespace game
{
  void init()
  {
    render::init(width_window, height_window, "brickbreak", width_window, height_window);
    input::init();
    time::init(60);

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

  void update()
  {
    int width_window, height_window;
    render::window::get_dimensions(&width_window, &height_window);
    if(input::key::key_left)
    {
      player.top_left.x -= 10.0f;
      if(player.top_left.x < 0.0f)
        player.top_left.x = 0.0f;
    }

    if(input::key::key_right)
    {
      player.top_left.x += 10.0f;
      if(player.top_left.x > width_window - player.size.x)
        player.top_left.x = width_window - player.size.x;
    }

    if(input::key::key_play)
      game_state = Play;

    if(game_state == Start)
    {
      ball.center.x = player.top_left.x + player.size.x / 2;
      ball.center.y = player.top_left.y - ball.radius;
    } else if (game_state == Play)
    {
      ball.center.x += 10.0f;
      ball.center.y -= 10.0f;
    }
  }

  void render()
  {
    render::loop::begin();

    game::level::render();

    // player
    // ---
    render::shapes::quad(player.top_left, player.size, player.color);
    // ---

    // ball
    // ---
    render::shapes::circle(ball.center, ball.radius, ball.color);
    // ---

    render::loop::end();
  }

  void cleanup()
  {
    render::cleanup();
  }
}
