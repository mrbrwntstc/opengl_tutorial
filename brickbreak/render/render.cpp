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
}
