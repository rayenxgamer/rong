#pragma once

#include <graphics/texture.h>
#include <graphics/renderer.h>
#include <math/vec2.h>

#define MAX_BALL_VELOCITY_X 6.0f
#define MAX_BALL_VELOCITY_Y 3.0f

struct ball{
  Rect* ball_rectangle;
  vec2 vel;
};

static float aabb_get_collision_time_between_(struct ball* ball_props, Rect* rect2);
void ball_update(struct ball *ball_props,float deltatime);
void ball_do_collisions(struct ball* ball, Rect* obstacle, Rect* player2rect);
void ball_bounce(struct ball *ball_props, Rect player);
