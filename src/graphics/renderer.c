#include "glad/gl.h"
#include "graphics/buffer.h"
#include <graphics/renderer.h>

struct rect renderer_initrect(float x, float y, int height, int width){

  uint32_t vao = vao_create();
  uint32_t vbo = vbo_create();

  const float vertices_buffer[] = {
     1.0f, 1.0f, 0.0f,
     1.0f,-1.0f, 0.0f,
    -1.0f,-1.0f, 0.0f,
    -1.0f, 1.0f, 0.0f,
  };

  const float indices_buffer[] = {
    0, 1, 3,
    1, 2, 3,
  };

  uint32_t ibo = ibo_create();
  ibo_bind(&ibo);
  ibo_buffer(sizeof(indices_buffer), indices_buffer, GL_STATIC_DRAW);

  vao_bind(&vao);
  vbo_bind(&vbo);
  vbo_buffer(sizeof(vertices_buffer), vertices_buffer, GL_STATIC_DRAW);

  vao_attrib(vao, vbo, 0, 3, GL_FLOAT, GL_FALSE , 3 * sizeof(float), 0);


  struct rect self = {x, y, height, width, vao, vbo};

  // more initialization code here
  return self;
};

void renderer_drawrect(struct rect rectangle){
  // rendering code here
  return;
};






