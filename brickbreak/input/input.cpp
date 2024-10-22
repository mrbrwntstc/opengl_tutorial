#include "../input.h"
#include "../render.h"

static void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
  
  if(key == GLFW_KEY_LEFT && (action == GLFW_PRESS || action == GLFW_REPEAT))
    input::key::key_left = true;
  else
    input::key::key_left = false;
  
  if(key == GLFW_KEY_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT))
    input::key::key_right = true;
  else
    input::key::key_right = false;

  if(key == GLFW_KEY_SPACE && (action == GLFW_PRESS || action == GLFW_REPEAT))
    input::key::key_space = true;
  else
    input::key::key_space = false;
}

namespace input
{
  void init()
  {
    glfwSetKeyCallback(render::window::window, glfw_key_callback);
  }
}