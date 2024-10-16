#include "render.h"

static const unsigned int width_window = 800;
static const unsigned int height_window = 600;

int main()
{
  render::init(width_window, height_window, "brickbreak", width_window, height_window);

  while(!render::window::should_close())
  {
    // render
    // ---
    render::loop::begin();

    render::shapes::quad(
      glm::vec3(400.0f, 400.0f, 0.0f),
      glm::vec3(50.0f, 50.0f, 0.0f),
      glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)
    );

    render::shapes::circle(
      glm::vec3(400.0f, 400.0f, 0.0f),
      20.0f,
      glm::vec4(1.0f, 0.0f, 1.0f, 1.0f)
    );

    render::loop::end();
  }

  // cleanup
  render::cleanup();

  return 0;
}
