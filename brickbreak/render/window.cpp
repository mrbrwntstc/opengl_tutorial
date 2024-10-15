#include "../render.h"

#include <stdexcept>

static void glfw_framebuffer_size_callback(GLFWwindow* window, int width_new, int height_new)
{
  glViewport(0, 0, width_new, height_new);
}

namespace render
{
namespace window
{
  GLFWwindow* window = NULL;

  void init(int width, int height, const char* title)
  {
    if(glfwInit() == GLFW_FALSE)
    {
      throw std::runtime_error("Failed to initialize GLFW\n");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if(!window)
    {
      glfwTerminate();
      throw std::runtime_error("Failed to create window\n");
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, glfw_framebuffer_size_callback);

    gladLoadGL();
  }
} // namespace window
} // namespace render
