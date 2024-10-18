#include "render.h"
#include "input.h"
#include "time.h"

#include <Windows.h>

static const unsigned int width_window = 800;
static const unsigned int height_window = 600;

int main()
{
  render::init(width_window, height_window, "brickbreak", width_window, height_window);
  input::init();
  time::init(60);

  // time
  // ---
  float frame_rate = 60.0f;
  unsigned int frame_count = 0;
  float frame_delay = 1.f / frame_rate;
  float dt = 0.f;
  float time_current = 0.f;
  float time_previous = 0.f;
  float frame_previous = 0.f;
  float frame_time = 0.f;
  // ---

  // level
  // ---
  const int num_rows = 6;
  const int num_cols = 10;
  const float block_width = 80.f;
  const float block_height = 20.f;
  glm::vec3 size_block = glm::vec3(block_width, block_height, 0.0f);
  glm::vec4 color_block = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
  float starting_x_block = 0.0f;
  float starting_y_block = 60.0f;
  glm::vec4 colors[] =
  {
    glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),    // red
    glm::vec4(1.0f, 0.647f, 0.0f, 1.0f),  // yellow
    glm::vec4(1.0f, 1.0f, 0.0f, 1.0f),    // orange
    glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),    // green
    glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),    // blue
    glm::vec4(0.5f, 0.0f, 0.5f, 1.0f)     // purple
  };
  // ---
  
  // player
  // ---
  glm::vec3 position_player = glm::vec3(100.0f, 500.0f, 0.0f);
  glm::vec3 size_player = glm::vec3(100.0f, 10.0f, 0.0f);
  glm::vec4 color_player = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
  // ---

  while(!render::window::should_close())
  {
    time::update();

    // input
    // ---
    if(input::key::key_left)
    {
      position_player.x -= 10.0f;
      if(position_player.x < 0.0f)
        position_player.x = 0.0f;
    }

    if(input::key::key_right)
    {
      position_player.x += 10.0f;
      if(position_player.x > width_window - size_player.x)
        position_player.x = width_window - size_player.x;
    }
    // ---

    // render
    // ---
    render::loop::begin();

    // level
    // ---
    for(int row = 0; row < num_rows; row++)
    {
      for(int col = 0; col < num_cols; col++)
      {
        render::shapes::quad(
          glm::vec3(
            starting_x_block + col * block_width,
            starting_y_block + row * block_height, 0.0f),
          size_block,
          colors[row]);
      }
    }
    // ---

    // player
    // ---
    render::shapes::quad(
      position_player,
      size_player,
      color_player);
    // ---

    // ball
    // ---
    float ball_x = position_player.x + size_player.x / 2;
    float ball_radius = 10.0f;
    float ball_y = position_player.y - ball_radius;
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
