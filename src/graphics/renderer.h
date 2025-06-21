#pragma once

#include <glad/gl.h>
#include <graphics/buffer.h>
#include <graphics/shader.h>
#include <graphics/texture.h>

struct rect{
  float x,y;
  float height;
  float width;
  uint32_t vao;
  uint32_t vbo;
  Texture texture;
};

struct rect renderer_initrect_tex(float x, float y, float height, float width, Texture texture);
void renderer_drawrect_tex(struct rect rectangle, struct shader shader);

struct rect renderer_initrect(float x, float y, float height, float width);
void renderer_drawrect(struct rect rectangle, struct shader shader);

