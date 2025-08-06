#pragma once

#include <graphics/defines/colors.h>
#include <glad/gl.h>
#include <graphics/buffer.h>
#include <graphics/shader.h>
#include <graphics/texture.h>
#include <math/aabb.h>

struct rect{
  float x,y;
  float height;
  float width;
  uint32_t vao_;
  uint32_t vbo_;
  Texture texture;
};

typedef struct {
  float window_height, window_width;
  Texture texture2D;
  uint32_t vao;
} background_props;

void renderer_drawaabbs();
void renderer_directdrawline(float xstart, float ystart, float xend, float yend, struct shader shader);

background_props renderer_initbackground(background_props props);
void renderer_drawbackground(background_props* props ,struct shader* shader);

struct rect renderer_initrect_tex(float x, float y, float height, float width, Texture texture);
void renderer_drawrect_tex(struct rect rectangle, struct shader* shader);

struct rect renderer_initrect(float x, float y, float height, float width);
void renderer_drawrect(struct rect rectangle, struct shader* shader);

struct rect renderer_init_particles(struct rect *rectangle, color color, struct shader* shader);
void renderer_drawrect_particle(struct rect *rectangle, color color, struct shader* shader);

