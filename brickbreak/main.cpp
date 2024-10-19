#include "render.h"
#include "input.h"
#include "time.h"

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
typedef struct Block
{
  glm::vec3 top_left;
  glm::vec4 color;
} block;
block blocks[num_rows * num_cols];
// ---

// player
// ---
typedef struct Player
{
  glm::vec3 position;
  glm::vec3 size;
  glm::vec4 color;
} player;
// ---

int main()
{
  render::init(width_window, height_window, "brickbreak", width_window, height_window);
  input::init();
  time::init(60);

  // level
  // ---
  for(int row = 0; row < num_rows; row++)
  {
    for(int col = 0; col < num_cols; col++)
    {
      glm::vec3 pos = glm::vec3(
        starting_x_block + col * block_width,
        starting_y_block + row * block_height,
        0.0f);

      blocks[row * num_cols + col] = {pos, colors[row]};
    }
  }
  // ---

  // player
  // ---
  player player = 
  {
    glm::vec3(100.0f, 500.0f, 0.0f),
    glm::vec3(100.0f, 10.0f, 0.0f),
    glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
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
    for(int i = 0; i < num_rows * num_cols; i++)
    {
      block block_current = blocks[i];
      render::shapes::quad(
        block_current.top_left,
        size_block,
        block_current.color);
    }
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
    float ball_x = player.position.x + player.size.x / 2;
    float ball_radius = 10.0f;
    float ball_y = player.position.y - ball_radius;
    render::shapes::circle(
      glm::vec3(ball_x, ball_y, 0.0f),
      ball_radius,
      glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    // ---

    render::loop::end();

    time::update_late();
  }

  // cleanup
  render::cleanup();

  return 0;
}
