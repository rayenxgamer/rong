#include "graphics/texture.h"
#include <game/window.h>
#include <graphics/renderer.h>
#include <stdio.h>

struct rect rectangledrawtest;
struct shader shader;
struct shader textureshader;
Texture cat;

void init(){
  cat = tex_create("../assets/cat.jpg", true);
  window_set_attributes(480, 640, "RONG: on the RENGINE!");
  shader = shader_create("../shaders/vs.glsl", "../shaders/fs.glsl");
  textureshader = shader_create("../shaders/textureshaders/vs.glsl", "../shaders/textureshaders/fs.glsl");
  rectangledrawtest = renderer_initrect_tex(-0.5f, -0.5f, 1.5f, 1.5f, cat);
};

void render(){
  glClearColor(0.8f, 0.2f, 0.8f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  renderer_drawrect_tex(rectangledrawtest, textureshader);
};

void tick(){
  if(window_is_pressed(GLFW_KEY_ESCAPE))
    window_set_should_close();
};
void update(){
};
void shutdown(){};

int main() {
  window_init(init, update, tick, render, shutdown);
  window_updateloop();
  return 0;
};
