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

// circle
// ---
#define NUM_SEGMENTS 100
static unsigned int vao_circle, vbo_circle;
static void init_circle()
{
  float vertices[NUM_SEGMENTS * 3];
  float theta = 2 * 3.14159256f / static_cast<float>(NUM_SEGMENTS);
  float tangential_factor = tanf(theta);
  float radial_factor = cosf(theta);
  float x = 1.f; // unit circle
  float y = 0;
  for(int i = 0; i < NUM_SEGMENTS; i++)
  {
    vertices[i * 3] = x;
    vertices[i * 3 + 1] = y;
    vertices[i * 3 + 2] = 0.0f;
    // calculate tangential vector
    float tx = -y;
    float ty = x;
    // add tangential vector
    x += tx * tangential_factor;
    y += ty * tangential_factor;
    // correct using radial factor
    x *= radial_factor;
    y *= radial_factor;
  }

  glGenVertexArrays(1, &vao_circle);
  glGenBuffers(1, &vbo_circle);
  
  glBindVertexArray(vao_circle);
  
  glBindBuffer(GL_ARRAY_BUFFER, vbo_circle);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  
  glBindVertexArray(0);
}

static void cleanup_circle()
{
  glDeleteVertexArrays(1, &vao_circle);
  glDeleteBuffers(1, &vbo_circle);
}
// ---

// convenience functions
// ---
void (*use_shader)(unsigned int) = &render::resource_manager::shader::use;
void (*set_shader_uniform_mat4)(unsigned int, const char*, const float*) = &render::resource_manager::shader::uniform::set_mat4;
void (*set_shader_uniform_vec4)(unsigned int, const char*, const float*) = &render::resource_manager::shader::uniform::set_vec4;
// ---

namespace render
{
namespace shapes
{
  void init()
  {
    init_quad();
    init_circle();
  }

  void cleanup()
  {
    cleanup_quad();
    cleanup_circle();
  }

  void quad(glm::vec3 position, glm::vec3 size, glm::vec4 color)
  {
    // set uniform variables
    unsigned int shader_program = render::resource_manager::shaders["engine"];
    use_shader(shader_program);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::scale(model, size);
    set_shader_uniform_mat4(shader_program, "model", &model[0][0]);
    set_shader_uniform_vec4(shader_program, "color", &color[0]);
    // draw
    glBindVertexArray(vao_quad);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_quad);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
  }

  void circle(glm::vec3 position, float radius, glm::vec4 color)
  {
    // set uniform variables
    unsigned int shader_program = render::resource_manager::shaders["engine"];
    use_shader(shader_program);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::scale(model, glm::vec3(radius, radius, 1.0f));
    set_shader_uniform_mat4(shader_program, "model", &model[0][0]);
    set_shader_uniform_vec4(shader_program, "color", &color[0]);
    // draw
    glBindVertexArray(vao_circle);
    glDrawArrays(GL_TRIANGLE_FAN, 0, NUM_SEGMENTS);
    glBindVertexArray(0);
  }
}
}
