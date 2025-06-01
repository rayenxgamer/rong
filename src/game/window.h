#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

struct window{
  int height;
  int width;
  char* title;
};

GLFWwindow* window_init(struct window window);
void window_shutdown(GLFWwindow* window);
