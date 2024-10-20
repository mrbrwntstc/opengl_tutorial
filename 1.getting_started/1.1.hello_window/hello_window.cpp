#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#define GLAD_GL_NO_PROTOTYPES
#include <glad/glad.h>

#include <iostream>

void glfw_framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
  // Window configuration and creation - GLFW + GLAD
  // ---
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello Window", NULL, NULL);
  if (!window)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwSetFramebufferSizeCallback(window, glfw_framebuffer_size_callback);
  glfwMakeContextCurrent(window);

  gladLoadGL();
  // ---

  // Main loop
  // ---
  while (!glfwWindowShouldClose(window))
  {
    // input
    // ---
    processInput(window);
    // ---

    // render
    // ---
    glfwSwapBuffers(window);
    glfwPollEvents();
    // ---
  }
  // ---

  // cleanup
  // ---
  glfwTerminate();
  // ---

  return 0;
}

void glfw_framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}