#pragma once

#include <math/vec3.h>

typedef struct {
  float r, g, b, a;
} Color;

#define REN_WHITE (Color){1.0f, 1.0f, 1.0f, 1.0f}
