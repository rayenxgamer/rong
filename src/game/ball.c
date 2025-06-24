#include <game/ball.h>

struct ball ball_init(struct rect rectangle, float initial_velocity){
  struct ball temp_ball = {rectangle.x ,rectangle.y, initial_velocity};
  return temp_ball;
};

void ball_update(struct ball ball, struct rect rectangle, float velocity, float gravity, float delta_time){
  rectangle.y += ball.vel;
  ball.vel += gravity;

  if(rectangle.y <= 0.0f)
    ball.vel = -ball.vel;
};
