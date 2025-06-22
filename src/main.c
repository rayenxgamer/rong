#include "graphics/camera.h"
#include "graphics/shader.h"
#include "graphics/texture.h"
#include <game/window.h>
#include <graphics/renderer.h>
#include <math/aabb.h>
#include <stdio.h>
#include <string.h>

#define PLAYER_VERT_SPEED 0.2f

struct rect rectangledrawtest, catrec;
struct shader shader;
struct shader textureshader;
struct camera cam;
Texture cat, cat2;

float player1x = -1.0f; float player1y = -0.5f;
float player2x = 0.5f; float player2y = -0.5f;

void init(){
  cam = camera_init_ortho((vec3){0.0f, 0.0f, 0.0f}, 640, 480, 1000);
  cat = tex_create("../assets/cat.jpg", true);
  window_set_attributes(480, 640, "RONG: on the RENGINE!");
  shader = shader_create("../shaders/vs.glsl", "../shaders/fs.glsl");
  textureshader = shader_create("../shaders/textureshaders/vs.glsl", "../shaders/textureshaders/fs.glsl");

  rectangledrawtest = renderer_initrect_tex(player1x, player1y, 1.0f, 1.0f, cat);
  catrec = renderer_initrect_tex(player2x, player2y, 1.0f, 1.0f, cat);
};

void render(){
  glClearColor(.0f, .0f, .0f, .0f);
  glClear(GL_COLOR_BUFFER_BIT);

  shader_setm4x4(textureshader, "projection", cam.projection_matrix);
  shader_setm4x4(textureshader, "view", cam.view_matrix);

  renderer_drawrect_tex(rectangledrawtest, textureshader);
  renderer_drawrect_tex(catrec, textureshader);
};

void tick(){
  if(window_is_pressed(GLFW_KEY_ESCAPE))
    window_set_should_close();

  if (window_is_pressed(GLFW_KEY_S))
    rectangledrawtest.y -= PLAYER_VERT_SPEED;

  if (window_is_pressed(GLFW_KEY_W))
    rectangledrawtest.y += PLAYER_VERT_SPEED;

  if (window_is_pressed(GLFW_KEY_K))
    rectangledrawtest.x -= PLAYER_VERT_SPEED;

  if (window_is_pressed(GLFW_KEY_I))
    rectangledrawtest.x += PLAYER_VERT_SPEED;

  printf("%f\t%f\n", rectangledrawtest.x, rectangledrawtest.y);

  if(aabb_check_collision(rectangledrawtest.x, rectangledrawtest.y, rectangledrawtest.width, rectangledrawtest.height
                       , catrec.x, catrec.y, catrec.width, catrec.height)){
    printf("ouchies, meow!\n");
  };
};
void update(){

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
