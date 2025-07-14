#include <game/ball.h>

void ball_update(struct ball *ball_props,float deltatime){

  if (ball_props->vel[1] > MAX_BALL_VELOCITY_Y) {
    ball_props->vel[1] = MAX_BALL_VELOCITY_Y;
  }

  if (ball_props->vel[0] > MAX_BALL_VELOCITY_X) {
    ball_props->vel[0] = MAX_BALL_VELOCITY_X;
  }

  if(ball_props->ball_rectangle->x <= 0.0f){
    ball_props->ball_rectangle->x = 320.0f;
    ball_props->ball_rectangle->y = 240.0f;
    ball_props->vel[0] = ball_props->vel[0] * -1.0;
  }

  if (ball_props->ball_rectangle->x + ball_props->ball_rectangle->width >= 680.0f) {
    ball_props->ball_rectangle->x = 320.0f;
    ball_props->ball_rectangle->y = 240.0f;
  }

  if(ball_props->ball_rectangle->y <= 0.0f){
    ball_props->vel[1] = -ball_props->vel[1];
    ball_props->ball_rectangle->y = 0.0f;
  }

  if (ball_props->ball_rectangle->y + ball_props->ball_rectangle->height >= 480.0f) {
    ball_props->vel[1] = -ball_props->vel[1];
    ball_props->ball_rectangle->y = 480.0f - ball_props->ball_rectangle->height;
  }
}

void ball_bounce(struct ball *ball_props, struct rect player){
  float distanceballrect = 0.0f;
  float center_of_paddle = 0.0f;
  // reminder, the rects's X is not the middle, it's the bottom left
    center_of_paddle = player.y + (player.height / 2.0f);
    distanceballrect = ball_props->ball_rectangle->y + (ball_props->ball_rectangle->height / 2.0f) - center_of_paddle;

  if (distanceballrect < 15.0f && distanceballrect > -15.0f) {
      // middle of the paddle itself
      ball_props->vel[0]= -ball_props->vel[0];
      ball_props->vel[1] = ball_props->vel[1] * .4f; // will decrease the y velocity making the ball go up and down slower
    }else if (distanceballrect < 40.0f && distanceballrect > 15.0f ){
      // just above the middle of the paddle
      ball_props->vel[0] = ball_props->vel[0] * -1.f;
      ball_props->vel[1] = ball_props->vel[1] * 1.6f;
    }else if (distanceballrect < 60.0f && distanceballrect > 40.0f ){
      // midway top paddle
      ball_props->vel[0] = ball_props->vel[0] * -1.f;
      ball_props->vel[1] = ball_props->vel[1] * 1.8f;
    }else if(distanceballrect < 70.0f && distanceballrect > 60.0f){
      // very top of paddle
      ball_props->vel[0] = ball_props->vel[0] * -1.f;
      ball_props->vel[1] = ball_props->vel[1] * 2.0f;
    }else if (distanceballrect < -15.0f && distanceballrect > -40.0f ){
      // just under middle bottom
      ball_props->vel[0] = ball_props->vel[0] * -1.f;
      ball_props->vel[1] = ball_props->vel[1] * 1.6f;
    }else if (distanceballrect < -40.0f && distanceballrect > -60.0f ){
      // midway bottom
      ball_props->vel[0] = ball_props->vel[0] * -1.0f;
      ball_props->vel[1] = ball_props->vel[1] * 1.8f;
    }else if (distanceballrect < -60.0f && distanceballrect > -72.5f ){
      // fully under
      ball_props->vel[0] = ball_props->vel[0] * -1.0f;
      ball_props->vel[1] = ball_props->vel[1] * 2.0f;
    }else{
      // top or bottom of the paddle itself
      ball_props->vel[0] = ball_props->vel[0] * -1.0f;
      ball_props->vel[1] = ball_props->vel[1] * -1.0f;
    };
}

static float aabb_get_collision_time_between_(struct ball* ball_props, struct rect* obstacle){
  // the normal of the object to be collided with
    float normal_x, normal_y;

    float distancetillentery_x, distancetillentery_y;
    float distancetillexit_x, distancetillexit_y;

    if (ball_props->vel[0] > 0.0f) {
      // TODO: check if this is supposed to be like this or from the top left
      distancetillentery_x = obstacle->x - (ball_props->ball_rectangle->x + ball_props->ball_rectangle->width);
      distancetillexit_x = (obstacle->x + obstacle->width) - ball_props->ball_rectangle->x;
    }else{
      distancetillentery_x = (obstacle->x + obstacle->width) - ball_props->ball_rectangle->x;
      distancetillexit_x = obstacle->x - (ball_props->ball_rectangle->x + ball_props->ball_rectangle->width);
    }

    if(ball_props->vel[1] > 0.0f){
      distancetillentery_y = obstacle->y - (ball_props->ball_rectangle->y + ball_props->ball_rectangle->height);
      distancetillexit_y = (obstacle->y + obstacle->height) - ball_props->ball_rectangle->y;
    }else{
      distancetillentery_y = (obstacle->y + obstacle->height) - ball_props->ball_rectangle->y;
      distancetillexit_y = obstacle->y - (ball_props->ball_rectangle->y + ball_props->ball_rectangle->height);
    }

  float timetillentery_x, timetillentery_y;
  float timetillexit_x, timetillexit_y;

  if (ball_props->vel[0] == 0.0f) {
    timetillentery_x = -(float)INFINITY;
    timetillexit_x = (float)INFINITY;
  }else{
    timetillentery_x = distancetillentery_x / ball_props->vel[0];
    timetillexit_x = distancetillexit_x / ball_props->vel[0];
  }

  if (ball_props->vel[1] == 0.0f) {
    timetillentery_y = -(float)INFINITY;
    timetillexit_y = (float)INFINITY;
  }else{
    timetillentery_y = distancetillentery_y / ball_props->vel[1];
    timetillexit_y = distancetillexit_y / ball_props->vel[1];
  }

  // check if collision occured at all;
  float enterytime = MAX(timetillentery_x, timetillentery_y);
  float exittime = MIN(timetillexit_x, timetillexit_y);

  // one way to check collision this way apparently
  if (enterytime > exittime || timetillentery_x < 0.0f && timetillentery_y < 0.0f || timetillentery_x > 1.0f || timetillentery_y > 1.0f) {
    return 1.0f;
  }else
  {
    if (timetillentery_x > timetillentery_y){
      if (distancetillentery_x < 0.0f)
      {
        normal_x = 1.0f;
        normal_y = 0.0f;
      }else
      {
        normal_x = -1.0f;
        normal_y = 0.0f;
      }
    }else{
      if (distancetillentery_y < 0.0f)
      {
        normal_x = 0.0f;
        normal_y = 1.0f;
      }else
      {
        normal_x = 0.0f;
        normal_y = -1.0f;
      }
    }
  }
  return enterytime;
};

void ball_do_collisions(struct ball* ball, struct rect* obstacle, struct rect* player2rect){
  const float middle_of_screen = 320.0f;

  float collisiontime;
  bool is_on_right_side;

  float percentage_of_velocity_change = 0.0f;

  if (ball->ball_rectangle->x < middle_of_screen) {
    collisiontime = aabb_get_collision_time_between_(ball, player2rect);
    is_on_right_side = false;
  }else{
    collisiontime = aabb_get_collision_time_between_(ball, obstacle);
    is_on_right_side = true;
  }

  const float max_time_untill_collision = 1.0f;
  float remainingtimeaftercollision = 1.0f - collisiontime; /* used for deflection after spending velocity for example
                                                            , not used for now */
  bool not_colliding = (collisiontime == max_time_untill_collision);

  if (not_colliding) {
    ball->ball_rectangle->x += ball->vel[0];
    ball->ball_rectangle->y  += ball->vel[1];
  /* printf("not collided\n"); */
  }else{
    ball->ball_rectangle->x  += ball->vel[0] * collisiontime;
    ball->ball_rectangle->y  += ball->vel[1] * collisiontime;

    if (is_on_right_side) { /* this means that the calculation will go based on the right side player's posisition */
      ball_bounce(ball, *obstacle);
    }else{
      ball_bounce(ball, *player2rect);
    }
  // printf("collided!\n");
  }
};
