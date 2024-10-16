#include "../render.h"

namespace render
{
  void init(int width, int height, const char* title, float width_screen, float height_screen)
  {
    window::init(width, height, title);
  }

  void cleanup()
  {
    window::cleanup();
    glfwTerminate();
  }
namespace loop
{
  void begin()
  {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
  }

  void end()
  {
    glfwSwapBuffers(render::window::window);
    glfwPollEvents();
  }
}
}
