#include "glad/gl.h"
#include <GLFW/glfw3.h>
#include "graphics/buffer.h"
#include "graphics/shader.h"
#include <graphics/renderer.h>
#include <math/mat4.h>

struct rect renderer_initrect_tex(float x, float y, float height, float width, Texture texture){
  uint32_t vao = vao_create();
  uint32_t vbo = vbo_create();
  uint32_t ibo = ibo_create();

  const float vertices_buffer[] = {
    0.0f,1.0f, 0.0f, 0.0f, 1.0f,
    1.0f,1.0f, 0.0f, 1.0f, 1.0f,
    1.0f,0.0f, 0.0f, 1.0f, 0.0f,

    0.0f,1.0f, 0.0f, 0.0f, 1.0f,
    1.0f,0.0f, 0.0f, 1.0f, 0.0f,
    0.0f,0.0f, 0.0f, 0.0f, 0.0f,
  };


  vao_bind(vao);
  vbo_bind(vbo);
  vbo_buffer(sizeof(vertices_buffer), vertices_buffer, GL_STATIC_DRAW);

  vao_attrib(vao, vbo, 0, 3,  GL_FLOAT,  GL_FALSE,  5 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  vao_attrib(vao, vbo, 1, 2, GL_FLOAT,GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  struct rect self = {x, y, height, width, vao, vbo, texture};

  return self;
};

void renderer_drawrect_tex(struct rect rectangle, struct shader shader){
  /* rendering code here */
  shader_bind(shader);
  mat4 model;
  mat4_identity(model);

  mat4_translate(model, (vec3){rectangle.x, rectangle.y, 0.0f});
  mat4_scalev_make(model,(vec3){rectangle.height, rectangle.width, 0.0f});

  tex_bind(rectangle.texture);
  shader_setm4x4(shader, "texture0", 0);
  shader_setm4x4(shader, "model", model);

  /* TODO: code to handle rotation */
  vao_bind(rectangle.vao);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  return;
};

struct rect renderer_initrect(float x, float y, float height, float width){

  uint32_t vao = vao_create();
  uint32_t vbo = vbo_create();
  uint32_t ibo = ibo_create();

  const float vertices_buffer[] = {
    0.0f,1.0f, 0.0f,
    1.0f,0.0f, 0.0f,
    0.0f,0.0f, 0.0f,

    0.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
  };

  vao_bind(vao);
  vbo_bind(vbo);
  vbo_buffer(sizeof(vertices_buffer), vertices_buffer, GL_STATIC_DRAW);

  vao_attrib(vao, vbo, 0, 3,  GL_FLOAT,  GL_FALSE,  3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  struct rect self = {x, y, height, width, vao, vbo};

  // more initialization code here
  return self;
};

void renderer_drawrect(struct rect rectangle, struct shader shader){
  /* rendering code here */
  shader_bind(shader);
  mat4 model;
  mat4_identity(model);

  mat4_translate(model, (vec3){rectangle.x, rectangle.y, 0.0f});
  mat4_scalev_make(model,(vec3){rectangle.height, rectangle.width, 0.0f});

  shader_setm4x4(shader, "model", model);

  /* TODO: code to handle rotation */
  vao_bind(rectangle.vao);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  return;
};






