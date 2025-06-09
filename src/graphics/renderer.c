#include "glad/gl.h"
#include "graphics/buffer.h"
#include "graphics/shader.h"
#include <graphics/renderer.h>

struct rect renderer_initrect(float x, float y, int height, int width){

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

  vao_bind(&vao);
  vbo_bind(&vbo);
  vbo_buffer(sizeof(vertices_buffer), vertices_buffer, GL_STATIC_DRAW);

  vao_attrib(vao, vbo, 0, 3, GL_FLOAT, GL_FALSE , 3 * sizeof(float), 0);

  struct rect self = {x, y, height, width, vao, vbo};

  // more initialization code here
  return self;
};

void renderer_drawrect(struct rect rectangle, struct shader shader){
  /* rendering code here */
  shader_bind(shader);

  /* TODO: code to handle rotation and translation */

  vao_bind(&rectangle.vao);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  vao_bind(0);
  return;
};






