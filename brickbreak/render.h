#ifndef __RENDER_H__
#define __RENDER_H__

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#define GLAD_GL_NO_PROTOTYPES
#include <glad/glad.h>

namespace render
{
  void init(int width_window, int height_window, const char* title_window, float width_screen, float height_screen);
  void cleanup();
namespace window
{
  extern GLFWwindow* window;
  void init(int width, int height, const char* title);
  inline void cleanup() { glfwDestroyWindow(window); }
  inline bool should_close() { return glfwWindowShouldClose(window); }
}
}

#endif // __RENDER_H__