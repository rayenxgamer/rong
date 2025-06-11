#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

typedef void (*RENGINE_FUNC_W)();

struct window{
  GLFWwindow* self;
  int height;
  int width;
  char* title;
  RENGINE_FUNC_W w_update, w_tick, w_init, w_render, w_shutdown;
};

extern struct window window;

void window_init(RENGINE_FUNC_W init, RENGINE_FUNC_W update, RENGINE_FUNC_W tick, RENGINE_FUNC_W render, RENGINE_FUNC_W shutdown);
void window_set_attributes(int height, int width, char* title);
void window_updateloop();
static void _init();
static void _update();
static void _tick();
static void _render();
static void _shutdown();
