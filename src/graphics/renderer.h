#pragma once

#include <glad/gl.h>
#include <graphics/buffer.h>

struct rect{
  float x,y;
  int height;
  int width;
  uint32_t vao;
  uint32_t vbo;
};

struct rect renderer_initrect(float x, float y, int height, int width);
void renderer_drawrect(struct rect rectangle);

