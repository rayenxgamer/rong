#include "graphics/camera.h"
#include "graphics/shader.h"
#include "graphics/texture.h"
#include <game/window.h>
#include <graphics/renderer.h>
#include <math/aabb.h>
#include <stdio.h>
#include <string.h>

#define PLAYER_VERT_SPEED 20.0f

struct rect player1, player2;
struct shader shader;
struct shader textureshader;
struct ortho_camera cam;
Texture cat, cat2;

float player1x = 540.0f; float player1y = 240.0f;
float player2x = 0.0f; float player2y = 240.0f;

void init(){
  cam = camera_init_ortho((vec3){0.0f, 0.0f, 0.0f}, 0.0f, 640.0f, 480.0f, 0.0f, -1.0f, 1.0f);
  cat = tex_create("../assets/cat.jpg", true);
  window_set_attributes(640, 480, "RONG: on the RENGINE!");
  shader = shader_create("../shaders/vs.glsl", "../shaders/fs.glsl");
  textureshader = shader_create("../shaders/textureshaders/vs.glsl", "../shaders/textureshaders/fs.glsl");

  player1 = renderer_initrect_tex(player1x, player1y, 100.0f, 100.0f, cat);
  player2 = renderer_initrect_tex(player2x, player2y, 100.0f, 100.0f, cat);
};

void render(){
  glClearColor(.0f, .0f, .0f, .0f);
  glClear(GL_COLOR_BUFFER_BIT);

  renderer_drawrect_tex(player1, textureshader);
  renderer_drawrect_tex(player2, textureshader);
};

void tick(){
  if(window_is_pressed(GLFW_KEY_ESCAPE))
    window_set_should_close();

  if (window_is_pressed(GLFW_KEY_S))
    player1.y -= PLAYER_VERT_SPEED;

  if (window_is_pressed(GLFW_KEY_W))
    player1.y += PLAYER_VERT_SPEED;

  if (window_is_pressed(GLFW_KEY_K))
    player2.y -= PLAYER_VERT_SPEED;

  if (window_is_pressed(GLFW_KEY_I))
    player2.y += PLAYER_VERT_SPEED;

  if(aabb_check_collision(player1.x, player1.y, player1.width, player1.height
                       , player2.x, player2.y, player2.width, player2.height)){
    printf("ouchies, meow!\n");
  };
};
void update(){
  camera_update(cam, textureshader);
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
