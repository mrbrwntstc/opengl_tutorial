#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#define GLAD_GL_NO_PROTOTYPES
#include <glad/glad.h>

#include <stdio.h>
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "render.h"
#include "render/resource_manager.h"

static const unsigned int width_window = 800;
static const unsigned int height_window = 600;

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

int main()
{
  render::init(width_window, height_window, "brickbreak", width_window, height_window);

  // shaders
  // ---
  render::resource_manager::add_shader("default", vertex_source, fragment_source);
  void (*shader_use)(unsigned int) = &render::resource_manager::shader::use;
  void (*shader_set_uniform_mat4)(unsigned int, const char*, const float*) = &render::resource_manager::shader::uniform::set_mat4;
  void (*shader_set_uniform_vec4)(unsigned int, const char*, const float*) = &render::resource_manager::shader::uniform::set_vec4;
  unsigned int shader_program = render::resource_manager::shaders["default"]; 
  // projection matrix will not change, so set it after the program is created
  shader_use(shader_program);
  glm::mat4 projection_mat4 = glm::ortho(0.0f, static_cast<float>(width_window), static_cast<float>(height_window), 0.0f, -1.0f, 1.0f);
  shader_set_uniform_mat4(shader_program, "projection", &projection_mat4[0][0]);
  // ---

  // initialize data for shader
  // ---
  unsigned int vao_quad, vbo_quad, ebo_quad;
  { // quad
    float vertices[] = {
      -0.5f,  0.5f, 0.0f, // top left
      0.5f,  0.5f, 0.0f, // top right
      0.5f, -0.5f, 0.0f, // bottom right
      -0.5f, -0.5f, 0.0f  // bottom left
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
  // ---

  unsigned int vao_circle, vbo_circle;
  #define NUM_SEGMENTS 100
  #define RADIUS 10.f
  { // circle
    float vertices[NUM_SEGMENTS * 3];
    float theta = 2 * 3.14159256f / static_cast<float>(NUM_SEGMENTS);
    float tangential_factor = tanf(theta);
    float radial_factor = cosf(theta);
    float x = RADIUS;
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
  
  while(!render::window::should_close())
  {
    // render
    // ---
    render::loop::begin();

    render::shapes::quad(
      glm::vec3(400.0f, 400.0f, 0.0f),
      glm::vec3(50.0f, 50.0f, 0.0f),
      glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)
    );

    shader_use(shader_program);
    // define uniforms
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(200.0f, 200.0f, 0.0f));
    model = glm::scale(model, glm::vec3(30.0f, 40.0f, 1.0f));
    shader_set_uniform_mat4(shader_program, "model", &model[0][0]);
    shader_set_uniform_vec4(shader_program, "color", &glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)[0]);
    // glUniformMatrix4fv(model_location, 1, false, &model[0][0]);
    // glUniform4f(color_location, 0.0f, 1.0f, 0.0f, 1.0f);
    // draw
    glBindVertexArray(vao_quad);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_quad);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(200.0f, 200.0f, 0.0f));
    shader_set_uniform_mat4(shader_program, "model", &model[0][0]);
    shader_set_uniform_vec4(shader_program, "color", &glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)[0]);
    // glUniformMatrix4fv(model_location, 1, false, &model[0][0]);
    // glUniform4f(color_location, 1.0f, 0.0f, 0.0f, 1.0f);
    glBindVertexArray(vao_circle);
    glDrawArrays(GL_TRIANGLE_FAN, 0, NUM_SEGMENTS);
    glBindVertexArray(0);

    render::loop::end();
  }

  // cleanup
  glDeleteVertexArrays(1, &vao_quad);
  glDeleteBuffers(1, &vbo_quad);
  glDeleteBuffers(1, &ebo_quad);

  render::cleanup();

  return 0;
}
