#include <game/window.h>
#include <graphics/renderer.h>
#include <stdio.h>

struct rect rectangledrawtest;
struct shader shader;

void init(){
  window_set_attributes(480, 640, "RONG: on the RENGINE!");
  shader = shader_create("../shaders/vs.glsl", "../shaders/fs.glsl");
  rectangledrawtest = renderer_initrect(-0.5f, -0.5f, 50, 50);
};

void render(){
  glClearColor(0.8f, 0.2f, 0.8f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  renderer_drawrect(rectangledrawtest, shader);
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
