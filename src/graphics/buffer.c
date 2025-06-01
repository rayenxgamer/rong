#include <graphics/buffer.h>


uint32_t vao_create(uint32_t *vao){
  glGenVertexArrays(1, vao);
  return *vao;
};

void vao_bind(uint32_t *vao){
  glBindVertexArray(*vao);
};

uint32_t vbo_create(uint32_t *vbo){
  glGenBuffers(1, vbo);
  return *vbo;
};

void vbo_bind(uint32_t *vbo){
  glBindBuffer(GL_ARRAY_BUFFER, *vbo);
};




