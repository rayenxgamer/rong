#include <game/window.h>
#include <game/game.h>
#include <stdio.h>

void init(){
  window_set_attributes(480, 640, "RONG: on the RENGINE!");
};

void render(){};
void tick(){};
void update(){
  glClearColor(0.8f, 0.2f, 0.8f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
};
void shutdown(){};

int main() {
  window_init(init, update, tick, render, shutdown);
  window_updateloop();
  return 0;
};
