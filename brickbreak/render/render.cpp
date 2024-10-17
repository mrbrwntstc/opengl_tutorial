#include "../render.h"
#include "resource_manager.h"

static const char *vertex_source = "#version 330 core\n"
  "layout (location = 0) in vec3 aPos;\n"
  "\n"
  "uniform mat4 model;\n"
  "uniform mat4 projection;\n"
  "\n"
  "void main()\n"
  "{\n"
  " gl_Position = projection * model * vec4(aPos, 1.0);"
  "}\0";

static const char *fragment_source = "#version 330 core\n"
  "out vec4 FragColor;\n"
  "\n"
  "uniform vec4 color;\n"
  "\n"
  "void main()\n"
  "{\n"
  " FragColor = color;\n"
  "}\0";


namespace render
{
  void init(int width, int height, const char* title, float width_screen, float height_screen)
  {
    window::init(width, height, title);
    render::resource_manager::add_shader("engine", vertex_source, fragment_source);
    unsigned int shader_engine = render::resource_manager::shaders["engine"];
    render::resource_manager::shader::use(shader_engine);
    glm::mat4 projection_mat4 = glm::ortho(0.0f, width_screen, height_screen, 0.0f, -1.0f, 1.0f);
    render::resource_manager::shader::uniform::set_mat4(shader_engine, "projection", &projection_mat4[0][0]);
    shapes::init();
  }

  void cleanup()
  {
    window::cleanup();
    shapes::cleanup();
    glfwTerminate();
  }
namespace loop
{
  void begin()
  {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
  }

  void end()
  {
    glfwSwapBuffers(render::window::window);
    glfwPollEvents();
  }
}
}
