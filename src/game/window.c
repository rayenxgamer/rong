#include "glad/gl.h"
#include "GLFW/glfw3.h"
#include <game/window.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define DEFAULT_WINDOW_WIDTH 480
#define DEFAULT_WINDOW_HEIGHT 640
#define TICK_SPEED 0.020f /* currently ecuvilant to roughly 20 milliseonds per tick */

struct window window;

static void _init(){
  window.w_init();
}

static void _update(float delta_time){
  window.w_update(delta_time);
  glfwSwapBuffers(window.self);
  glfwPollEvents();
}

static void _tick(){
  window.w_tick();
}

static void _render(){
  window.w_render();
}

static void _shutdown(){
  window.w_shutdown();
  glfwTerminate();
}

static void _error_callback(int error, const char* description){
  printf("%s\n", description);
}


static void _framebuffer_size_callback(GLFWwindow* window, int width, int height){
  glViewport(0, 0, width, height);
};

void window_init(RENGINE_FUNC_W init, RENGINE_FUNC_W_DT update, RENGINE_FUNC_W tick, RENGINE_FUNC_W render, RENGINE_FUNC_W shutdown){
  window.w_init = init;
  window.w_update = update;
  window.w_tick = tick;
  window.w_render = render;
  window.w_shutdown = shutdown;

  if (!glfwInit()) {
    fprintf(stderr, "glfw failed to init!\n");
    exit(1);
  }

  glfwWindowHint(GLFW_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_VERSION_MINOR, 3);

  /* bugged for some reason?
     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); */

  #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  #endif

  glfwSetErrorCallback(_error_callback);

  // TODO:: glfwsetWindowSizeCallback();

  /* basic window data, can be changed with window_set_attributes */
  window.self = glfwCreateWindow(640, 480, "untitled but def not rong", NULL, NULL);

  glfwMakeContextCurrent(window.self);

  if (window.self == NULL) {
    fprintf(stderr, "failed to create GLFW window! that's bad wtf how did this happen\n");
    exit(1);
  }


  if (!gladLoadGL(glfwGetProcAddress)) {
    fprintf(stderr, "failed to load glad using GLFW's proc address! this is really bad? check glad!\n");
    exit(1);
  };

  glfwSetFramebufferSizeCallback(window.self, _framebuffer_size_callback);
  glfwSwapInterval(1);
};

void window_set_attributes(int width, int height, char* title){
  glfwSetWindowTitle(window.self, title);
  glfwSetWindowSize(window.self, width, height);
};

bool window_is_pressed(int key){
  switch (glfwGetKey(window.self, key)) {
    case GLFW_PRESS:
    return 1;
    default:
    return 0;
  }
};

void window_set_should_close(){
  glfwSetWindowShouldClose(window.self, true);
}

float window_get_width(){
  return window.width;
};

float window_get_height(){
  return window.height;
};

void window_updateloop(){
  _init();

  float time = 0.0f, last_frame = 0.0f, dt = 0.0f;
  float time_elapsed_milli = 0.0f;

  while(!glfwWindowShouldClose(window.self)){
  /* my understanding of this is that time gets updated, substracted from the older time to get the delta time
    then the older time gets updated to be the current time again, effectively getting the diffrence between them */
    time = (float)glfwGetTime();
    dt = time - last_frame;
    time_elapsed_milli += dt;
    last_frame = time;

    if (time_elapsed_milli >= TICK_SPEED) {
      time_elapsed_milli = .0f;
      _tick();
    }

    _render();
    _update(dt);
  }

  _shutdown();
};
