#pragma once

#include <glad/gl.h>
#include <math/common.h>
#include <stb_image.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct {
  uint32_t handle;
  const char* path;
  bool flipped;
} Texture;

Texture tex_create(const char* path, bool flipped);
void tex_bind(Texture texture);
