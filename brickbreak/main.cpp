#include "render.h"
#include "input.h"
#include "time.h"
#include "game.h"

#include <Windows.h>

static const unsigned int width_window = 800;
static const unsigned int height_window = 600;

// level
// ---
const int num_rows = 6;
const int num_cols = 10;
const float block_width = 80.f;
const float block_height = 20.f;
glm::vec3 size_block = glm::vec3(block_width, block_height, 0.0f);
float starting_x_block = 0.0f;
float starting_y_block = 60.0f;
glm::vec4 colors[] =
{
  glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),    // red
  glm::vec4(1.0f, 0.647f, 0.0f, 1.0f),  // orange
  glm::vec4(1.0f, 1.0f, 0.0f, 1.0f),    // yellow
  glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),    // green
  glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),    // blue
  glm::vec4(0.5f, 0.0f, 0.5f, 1.0f)     // purple
};
struct Block
{
  glm::vec3 top_left;
  glm::vec4 color;
};
// ---

// player
// ---
struct Player
{
  glm::vec3 position;
  glm::vec3 size;
  glm::vec4 color;
};
// ---

// ball
// ---
struct Ball
{
  glm::vec3 position;
  glm::vec3 velocity;
  glm::vec4 color;
};
// ---

int main()
{
  render::init(width_window, height_window, "brickbreak", width_window, height_window);
  input::init();
  time::init(60);

  game::init();

  // player
  // ---
  Player player = 
  {
    glm::vec3(100.0f, 500.0f, 0.0f),
    glm::vec3(100.0f, 10.0f, 0.0f),
    glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
  };
  // ---

  // ball
  // ---
  float ball_x = player.position.x + player.size.x / 2;
  float ball_radius = 10.0f;
  float ball_y = player.position.y - ball_radius;
  Ball ball = 
  {
    glm::vec3(ball_x, ball_y, 0.0f),
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)
  };
  // ---

  while(!render::window::should_close())
  {
    time::update();

    // input
    // ---
    if(input::key::key_left)
    {
      player.position.x -= 10.0f;
      if(player.position.x < 0.0f)
        player.position.x = 0.0f;
    }

    if(input::key::key_right)
    {
      player.position.x += 10.0f;
      if(player.position.x > width_window - player.size.x)
        player.position.x = width_window - player.size.x;
    }
    // ---

    // render
    // ---
    render::loop::begin();

    // level
    // ---
    game::level::render();
    // ---

    // player
    // ---
    render::shapes::quad(
      player.position,
      player.size,
      player.color);
    // ---

    // ball
    // ---
    ball.position.x = player.position.x + player.size.x / 2;
    ball.position.y = player.position.y - ball_radius;
    render::shapes::circle(
      ball.position,
      ball_radius,
      ball.color);
    // ---

    render::loop::end();

    time::update_late();
  }

  // cleanup
  render::cleanup();

  return 0;
}
