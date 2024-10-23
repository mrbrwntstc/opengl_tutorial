#include "../game.h"
#include "../render.h"

static constexpr int num_rows = 6;
static constexpr int num_cols = 10;
static float block_width = 80.f;
static float block_height = 20.f;
static glm::vec3 size_block = glm::vec3(block_width, block_height, 0.0f);
static float starting_x_block = 0.0f;
static float starting_y_block = 60.0f;

static glm::vec4 colors[] =
{
  glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),    // red
  glm::vec4(1.0f, 0.647f, 0.0f, 1.0f),  // orange
  glm::vec4(1.0f, 1.0f, 0.0f, 1.0f),    // yellow
  glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),    // green
  glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),    // blue
  glm::vec4(0.5f, 0.0f, 0.5f, 1.0f)     // purple
};

static game::component::Block blocks[num_rows * num_cols];

namespace game
{
namespace level
{
  void init()
  {
    for (int row = 0; row < num_rows; row++)
    {
      for (int col = 0; col < num_cols; col++)
      {
        glm::vec3 pos = glm::vec3(
          starting_x_block + col * block_width,
          starting_y_block + row * block_height,
          0.0f);

        blocks[row * num_cols + col] = {pos, colors[row], size_block};
      }
    }
  }

  void render()
  {
    for(game::component::Block block : blocks)
    {
      render::shapes::quad(block.top_left, block.size, block.color);
    }
  }

  void check_collision(game::component::Ball &ball)
  {
    for(game::component::Block block : blocks)
    {
      glm::vec3 block_halfsize = glm::vec3(block.size.x / 2, block.size.y / 2, 0.0f);
      glm::vec3 block_center = glm::vec3(block.top_left.x + block_halfsize.x, block.top_left.y + block_halfsize.y, 0.0f);
      glm::vec3 distance_centers = ball.center - block_center;
      glm::vec3 distance_centers_clamped = glm::clamp(distance_centers, -block_halfsize, block_halfsize);
      glm::vec3 point_collision_block = block_center + distance_centers_clamped;
      glm::vec3 ball_to_block = point_collision_block - ball.center;
      float distance = glm::length(ball_to_block);
      if(distance < ball.radius)
      {
        // test algorithm
        ball.velocity.y = -ball.velocity.y;
      }
    }
  }
}
}
