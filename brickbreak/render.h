#ifndef __RENDER_H__
#define __RENDER_H__

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#define GLAD_GL_NO_PROTOTYPES
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
namespace loop
{
  void begin();
  void end();
}
namespace shapes
{
  void init();
  void cleanup();
  void quad(glm::vec3 position, glm::vec3 size, glm::vec4 color);
  void circle(glm::vec3 position, float radius, glm::vec4 color);
}
}

#endif // __RENDER_H__