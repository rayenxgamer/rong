#include "atlas.h"

Atlas atlas_create(uint32_t size_x, uint32_t size_y, Texture* texture){
  return (Atlas){size_x, size_y, texture};
};

void* atlas_get_texture_at(Atlas* atlas ,uint32_t x, uint32_t y){
  vec4 pixel_coords;
  vec4 uvs = {.0,.0,.0,.0};
  void* p;

  float i = 0.0f;
  float j = 0.0f;

  pixel_coords[0] = (x * atlas->size_x_) / atlas->texture->width;
  pixel_coords[1] = ((y * atlas->size_y_) + atlas->size_y_) / atlas->texture->height;

  pixel_coords[2] = ((x * atlas->size_x_) + atlas->size_x_) / atlas->texture->width;
  pixel_coords[3] = (y * atlas->size_y_) / atlas->texture->height;

  vec4_print(pixel_coords);
  vec4_copy(uvs, pixel_coords);

  p = &uvs;
  return (vec4*)p;
};

