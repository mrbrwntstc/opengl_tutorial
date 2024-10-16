#include "../render.h"
#include "resource_manager.h"

// quad
// ---
static unsigned int vao_quad, vbo_quad, ebo_quad;
// create a unit square
static void init_quad()
{
  float vertices[] = {
    0.0f, 1.0f, 0.0f, // top left
    1.0f, 1.0f, 0.0f, // top right
    1.0f, 0.0f, 0.0f, // bottom right
    0.0f, 0.0f, 0.0f, // bottom left
  };

  unsigned int indices[] = {
    0, 1, 2,
    0, 2, 3
  };

  glGenVertexArrays(1, &vao_quad);
  glGenBuffers(1, &vbo_quad);
  glGenBuffers(1, &ebo_quad);

  glBindVertexArray(vao_quad);

  glBindBuffer(GL_ARRAY_BUFFER, vbo_quad);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_quad);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);
}
static void cleanup_quad()
{
  glDeleteVertexArrays(1, &vao_quad);
  glDeleteBuffers(1, &vbo_quad);
  glDeleteBuffers(1, &ebo_quad);
}
// ---

namespace render
{
namespace shapes
{
  void init()
  {
    init_quad();
  }

  void cleanup()
  {
    cleanup_quad();
  }

  void quad(glm::vec3 position, glm::vec3 size, glm::vec4 color)
  {
    // set uniform variables
    unsigned int shader_program = render::resource_manager::shaders["default"];
    render::resource_manager::shader::use(shader_program);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::scale(model, size);
    render::resource_manager::shader::uniform::set_mat4(shader_program, "model", &model[0][0]);
    render::resource_manager::shader::uniform::set_vec4(shader_program, "color", &color[0]);
    // draw
    glBindVertexArray(vao_quad);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_quad);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
  }
}
}
