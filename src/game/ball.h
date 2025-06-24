#pragma once

#include <graphics/texture.h>
#include <graphics/renderer.h>

struct ball{
  float x, y;
  float vel;
};

struct ball ball_init(struct rect rectangle, float initial_velocity);
void ball_update(struct ball ball, struct rect rectangle,float velocity, float gravity, float delta_time);
