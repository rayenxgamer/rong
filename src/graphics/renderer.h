#pragma once

#include <graphics/defines/colors.h>
#include <graphics/atlas/atlas.h>
#include <graphics/buffer.h>
#include <graphics/shader.h>
#include <graphics/texture.h>
#include <math/aabb.h>

typedef struct{
  float x,y;
  float height;
  float width;
  uint32_t vao_;
  uint32_t vbo_;
  Texture texture;
} Rect;

typedef struct {
  float window_height, window_width;
  Texture texture2D;
  uint32_t vao;
} background_props;

void renderer_drawaabbs();
void renderer_directdrawline(float xstart, float ystart, float xend, float yend, Shader shader);

background_props renderer_initbackground(background_props props);
void renderer_drawbackground(background_props* props ,Shader* shader);

Rect renderer_initrect_tex(float x, float y, float height, float width, Texture texture);
void renderer_drawrect_tex(Rect rectangle, Shader* shader);

Rect renderer_initrect(float x, float y, float height, float width);
void renderer_drawrect(Rect rectangle, Shader* shader);

Rect renderer_init_particles(Rect *rectangle, Color color, Shader* shader);
void renderer_drawrect_particle(Rect *rectangle, Color color, Shader* shader);

Rect renderer_initatlas(Atlas atlas, vec4 position , float x, float y, float height, float width);
void renderer_drawfromatlas(Atlas atlas,Rect* rectangle , Shader* shader);
void renderer_clear_color(GLclampf red, GLclampf blue, GLclampf green, GLclampf alpha);
