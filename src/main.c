#include "game/ball.h"
#include "graphics/camera.h"
#include "graphics/shader.h"
#include "graphics/texture.h"
#include "math/common.h"
#include <math/aabb.h>
#include <game/window.h>
#include <graphics/renderer.h>
#include <stdio.h>
#include <string.h>

#define PLAYER_VERT_SPEED 20.0f
#define GRAVITY -1.0f

struct rect player1, player2, ball_rect;
struct shader debugshader;
struct shader textureshader;
struct ortho_camera cam;
Texture cat, string_ball, twach;
struct ball ball;

float ball_velocity = 10.0f;

float player1x = 540.0f; float player1y = 240.0f;
float player2x = 0.0f; float player2y = 240.0f;

void init(){
  cam = camera_init_ortho((vec3){0.0f, 0.0f, 0.0f}, 0.0f, 640.0f, 0.0f, 480.0f, -1.0f, 1.0f);
  cat = tex_create("../assets/cat.jpg", true);
  string_ball = tex_create("../assets/string_ball.jpg", true);
  twach = tex_create("../assets/twach.jpg", true);
  window_set_attributes(640, 480, "RONG: on the RENGINE!");
  debugshader = shader_create("../shaders/vs.glsl", "../shaders/fs.glsl");
  textureshader = shader_create("../shaders/textureshaders/vs.glsl", "../shaders/textureshaders/fs.glsl");

  ball_rect = renderer_initrect_tex(320.0f, 240.0f, 50.0f, 50.0f, string_ball);
  player1 = renderer_initrect_tex(player1x, player1y, 100.0f, 100.0f, cat);
  player2 = renderer_initrect_tex(player2x, player2y, 100.0f, 100.0f, twach);
  ball = ball_init(ball_rect, ball_velocity);
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

  if (window_is_pressed(GLFW_KEY_L))
    ball_rect.y += PLAYER_VERT_SPEED;
  if (window_is_pressed(GLFW_KEY_J))
    ball_rect.y -= PLAYER_VERT_SPEED;

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

  /* TODO: ACTUALLY MAKE REFLECTION */
  // ball_rect.y += ball_velocity;
  ball_rect.x += ball_velocity;

  if(ball_rect.x <= 0.0f){
    ball_velocity = -ball_velocity;
    ball_rect.x = 0.0f;
  }

  if (ball_rect.x + ball_rect.width >= 680.0f) {
    ball_velocity = -ball_velocity;
    ball_rect.x = 680.0f - ball_rect.height;
  }

  if(ball_rect.y <= 0.0f){
    ball_velocity = -ball_velocity;
    ball_rect.y = 0.0f;
  }

  if (ball_rect.y + ball_rect.height >= 480.0f) {
    ball_velocity = -ball_velocity;
    ball_rect.y = 480.0f - ball_rect.height;
  }

 if(aabb_check_collision(player1.x, player1.y, player1.width, player1.height, ball_rect.x, ball_rect.y, ball_rect.width, ball_rect.height)){
    ball_velocity = -ball_velocity;
  }

 if(aabb_check_collision(player2.x, player2.y, player2.width, player2.height, ball_rect.x, ball_rect.y, ball_rect.width, ball_rect.height)){
    ball_velocity = -ball_velocity;
  }

  printf("%f\t\n", ball_velocity);
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
