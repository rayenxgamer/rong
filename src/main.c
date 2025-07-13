#include "graphics/camera.h"
#include "graphics/shader.h"
#include "graphics/texture.h"
#include "math/common.h"
#include <math/aabb.h>
#include <math/vec2.h>
#include <game/window.h>
#include <graphics/renderer.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PLAYER_VERT_SPEED 8.0f
#define GRAVITY -1.0f

struct rect player1, player2, ball_rect;
struct shader debugshader;
struct shader textureshader;
struct ortho_camera cam;
Texture cat, string_ball, twach;

#define MAX_BALL_VELOCITY_X 7.0f
#define MAX_BALL_VELOCITY_Y 5.0f

float ball_initial_velocity_x = 0.0f;
float ball_initial_velocity_y = 0.0f;
float ball_velocity_x = 0.0f;
float ball_velocity_y = 0.0f;

vec2 player1_coords;
vec2 player2_coords;

float aabb_get_collision_time(struct rect* ball, struct rect* playerrect);
void ball_bounce(struct rect* ball, struct rect player);

void ball_do_collisions(struct rect* ball, struct rect* playerrect, struct rect* player2rect){
  const float middle_of_screen = 320.0f;

  float collisiontime;
  bool is_on_right_side;

  float percentage_of_velocity_change = 0.0f;

  if (ball->x < middle_of_screen) {
    collisiontime = aabb_get_collision_time(ball, player2rect);
    is_on_right_side = false;
  }else{
    collisiontime = aabb_get_collision_time(ball, playerrect);
    is_on_right_side = true;
  }

  const float max_time_untill_collision = 1.0f;
  float remainingtimeaftercollision = 1.0f - collisiontime; /* used for deflection after spending velocity for example
                                                            , not used for now */
  bool not_colliding = (collisiontime == max_time_untill_collision);

  if (not_colliding) {
    ball->x += ball_velocity_x;
    ball->y  += ball_velocity_y;
  /* printf("not collided\n"); */
  }else{
    ball->x  += ball_velocity_x * collisiontime;
    ball->y  += ball_velocity_y * collisiontime;

    if (is_on_right_side) { /* this means that the calculation will go based on the right side player's posisition */
      ball_bounce(&ball_rect, *playerrect);
    }else{
      ball_bounce(&ball_rect, *player2rect);
    }
  // printf("collided!\n");
  }
};


void init(){
  player1_coords[0] = 590.0f; player1_coords[1] = 180.0f;
  player2_coords[0] = 25.0f; player2_coords[1] = 180.0f;

  srand(time(NULL));
  ball_velocity_y = rand_range(-5, 5);
  ball_velocity_x = rand_range(-5, 5);

  ball_initial_velocity_x = ball_velocity_x;
  ball_initial_velocity_y = ball_velocity_y;

  cam = camera_init_ortho((vec3){0.0f, 0.0f, 0.0f}, 0.0f, 640.0f, 0.0f, 480.0f, -1.0f, 1.0f);
  cat = tex_create("../assets/cat.jpg", true);
  string_ball = tex_create("../assets/string_ball.jpg", true);
  twach = tex_create("../assets/twach.jpg", true);
  window_set_attributes(640, 480, "RONG: on the RENGINE!");
  debugshader = shader_create("../shaders/vs.glsl", "../shaders/fs.glsl");
  textureshader = shader_create("../shaders/textureshaders/vs.glsl", "../shaders/textureshaders/fs.glsl");

  ball_rect = renderer_initrect_tex(320.0f, 240.0f, 25.0f, 25.0f, string_ball);
  player1 = renderer_initrect_tex(player1_coords[0], player1_coords[1], 120.0f, 25.0f, cat);
  player2 = renderer_initrect_tex(player2_coords[0], player2_coords[1], 120.0f, 25.0f, twach);
};

void render(){
  glClearColor(.0f, .0f, .0f, .0f);
  glClear(GL_COLOR_BUFFER_BIT);

  renderer_drawrect_tex(player1, textureshader);
  renderer_drawrect_tex(player2, textureshader);

  renderer_drawrect_tex(ball_rect, textureshader);
};

void tick(){
  if(window_is_pressed(GLFW_KEY_ESCAPE))
    window_set_should_close();

  /* if(aabb_check_collision(player1.x, player1.y, player1.width, player1.height
                       , player2.x, player2.y, player2.width, player2.height)){
    printf("ouchies, meow!\n");
  }; */

  /* remember that the players are drawn from the bottom left */

};

void update(float deltatime){
  camera_update(cam, textureshader);
  camera_update(cam, debugshader);

  if (window_is_pressed(GLFW_KEY_S))
    player1.y -= PLAYER_VERT_SPEED;

  if (window_is_pressed(GLFW_KEY_W))
    player1.y += PLAYER_VERT_SPEED;

  if (window_is_pressed(GLFW_KEY_K))
    player2.y -= PLAYER_VERT_SPEED;

  if (window_is_pressed(GLFW_KEY_I))
    player2.y += PLAYER_VERT_SPEED;

  //
  // ---------- debugging ----------
  if (window_is_pressed(GLFW_KEY_EQUAL))
    ball_velocity_x += 1.0f;
  if (window_is_pressed(GLFW_KEY_MINUS))
    ball_velocity_y -= 1.0f;
  // -------------------------------;
  //

  ball_do_collisions(&ball_rect, &player1, &player2);

  if (ball_velocity_y > MAX_BALL_VELOCITY_Y) {
    ball_velocity_y = MAX_BALL_VELOCITY_Y;
  }

  if (ball_velocity_x > MAX_BALL_VELOCITY_X) {
    ball_velocity_x = MAX_BALL_VELOCITY_X;
  }

  if (player1.y + player1.height >= 480.0f){
    player1.y = 480.0f - player1.height;
  };
  if(player1.y <= 0.0f){
    player1.y = 0.0f;
  };

  if (player2.y + player2.height >= 480.0f){
    player2.y = 480.0f - player2.height;
  };
  if(player2.y <= 0.0f){
    player2.y = 0.0f;
  };

  if(ball_rect.x <= 0.0f){
    ball_rect.x = 320.0f;
    ball_rect.y = 240.0f;
    ball_velocity_x = ball_velocity_x * -1.0;
  }

  if (ball_rect.x + ball_rect.width >= 680.0f) {
    ball_rect.x = 320.0f;
    ball_rect.y = 240.0f;
  }

  if(ball_rect.y <= 0.0f){
    ball_velocity_y = -ball_velocity_y;
    ball_rect.y = 0.0f;
  }

  if (ball_rect.y + ball_rect.height >= 480.0f) {
    ball_velocity_y = -ball_velocity_y;
    ball_rect.y = 480.0f - ball_rect.height;
  }
};

void shutdown(){};

int main(int argc, char* argv[]) {
  if (argc == 2) {
    int parameter_count = 2;
    char debug_string[] = "--debug";
    char help_string[] = "--help";
    if (memcmp(argv[1],debug_string, strlen(debug_string)) == 0) {
      #ifndef RENGINE_DEBUG
      #define RENGINE_DEBUG
      #endif
      printf("entered debug mode\n");
    }else if (memcmp(argv[1], help_string, strlen(help_string)) == 0) {
      printf("current launch options:\n");
      printf("\t--debug to enable debug mode\n");
      printf("\t--help to print this again!\n");
    }else{
      printf("use '--help' for launch parameters!");
    }
  }

  window_init(init, update, tick, render, shutdown);
  window_updateloop();
  return 0;
};


float aabb_get_collision_time(struct rect* ball, struct rect* playerrect){
  // the normal of the object to be collided with
    float normal_x, normal_y;

    float distancetillentery_x, distancetillentery_y;
    float distancetillexit_x, distancetillexit_y;

    if (ball_velocity_x > 0.0f) {
      // TODO: check if this is supposed to be like this or from the top left
      distancetillentery_x = playerrect->x - (ball->x + ball->width);
      distancetillexit_x = (playerrect->x + playerrect->width) - ball->x;
    }else{
      distancetillentery_x = (playerrect->x + playerrect->width) - ball->x;
      distancetillexit_x = playerrect->x - (ball->x + ball->width);
    }

    if(ball_velocity_y > 0.0f){
      distancetillentery_y = playerrect->y - (ball->y + ball->height);
      distancetillexit_y = (playerrect->y + playerrect->height) - ball->y;
    }else{
      distancetillentery_y = (playerrect->y + playerrect->height) - ball->y;
      distancetillexit_y = playerrect->y - (ball->y + ball->height);
    }

  float timetillentery_x, timetillentery_y;
  float timetillexit_x, timetillexit_y;

  if (ball_velocity_x == 0.0f) {
    timetillentery_x = -(float)INFINITY;
    timetillexit_x = (float)INFINITY;
  }else{
    timetillentery_x = distancetillentery_x / ball_velocity_x;
    timetillexit_x = distancetillexit_x / ball_velocity_x;
  }

  if (ball_velocity_y == 0.0f) {
    timetillentery_y = -(float)INFINITY;
    timetillexit_y = (float)INFINITY;
  }else{
    timetillentery_y = distancetillentery_y / ball_velocity_y;
    timetillexit_y = distancetillexit_y / ball_velocity_y;
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

void ball_bounce(struct rect* ball, struct rect player){
    float distanceballrect = 0.0f;
    float center_of_paddle = 0.0f;
    // reminder, the rects's X is not the middle, it's the bottom left
      center_of_paddle = player.y + (player.height / 2.0f);
      distanceballrect = ball->y + (ball->height / 2.0f) - center_of_paddle;
    if (distanceballrect < 15.0f && distanceballrect > -15.0f) {
        // middle of the paddle itself
        ball_velocity_x = -ball_velocity_x;
        ball_velocity_y = ball_velocity_y * .4f; // will decrease the y velocity making the ball go up and down slower
      }else if (distanceballrect < 40.0f && distanceballrect > 15.0f ){
        // just above the middle of the paddle
        ball_velocity_x = ball_velocity_x * -1.f;
        ball_velocity_y = ball_velocity_y * 1.6f;
      }else if (distanceballrect < 60.0f && distanceballrect > 40.0f ){
        // midway top paddle
        ball_velocity_x = ball_velocity_x * -1.f;
        ball_velocity_y = ball_velocity_y * 1.8f;
      }else if(distanceballrect < 70.0f && distanceballrect > 60.0f){
        // very top of paddle
        ball_velocity_x = ball_velocity_x * -1.f;
        ball_velocity_y = ball_velocity_y * 2.0f;
      }else if (distanceballrect < -15.0f && distanceballrect > -40.0f ){
        // just under middle bottom
        ball_velocity_x = ball_velocity_x * -1.f;
        ball_velocity_y = ball_velocity_y * 1.6f;
      }else if (distanceballrect < -40.0f && distanceballrect > -60.0f ){
        // midway bottom
        ball_velocity_x = ball_velocity_x * -1.0f;
        ball_velocity_y = ball_velocity_y * 1.8f;
      }else if (distanceballrect < -60.0f && distanceballrect > -72.5f ){
        // fully under
        ball_velocity_x = ball_velocity_x * -1.0f;
        ball_velocity_y = ball_velocity_y * 2.0f;
      }else{
        // top or bottom of the paddle itself
        ball_velocity_x = ball_velocity_x * -1.0f;
        ball_velocity_y = ball_velocity_y * -1.0f;
      };

};
