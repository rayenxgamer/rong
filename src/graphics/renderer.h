#pragma once

struct rect{
  float x,y;
  int height;
  int width;
};

struct rect renderer_initrect(float x, float y, int height, int width);
void renderer_drawrect(struct rect rectangle);

