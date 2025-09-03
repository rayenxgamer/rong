#pragma once

#include <stdint.h>
#include <assert.h>

#include <graphics/texture.h>
#include <math/vec2.h>
#include <math/vec4.h>

typedef struct {
  uint32_t size_x_, size_y_;
  Texture* texture;
} Atlas;

Atlas atlas_create(uint32_t size_x, uint32_t size_y,Texture* texture);
void* atlas_get_texture_at(Atlas* atlas ,uint32_t x, uint32_t y);
