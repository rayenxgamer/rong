#pragma once

#include "math/vec2.h"
#include "graphics/renderer.h"
#include "graphics/shader.h"
#include "graphics/defines/colors.h"

struct particle {
  struct rect particle_rectangle;
  color color;
  float lifetime;
};

void particle_emit(struct particle* particle, struct shader* shader);

void particles_update();

/* make particle header actually have structs and function definitions?? */
