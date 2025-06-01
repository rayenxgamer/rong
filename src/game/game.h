#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

int game_run(GLFWwindow* window);
void game_update(GLFWwindow* window);
void game_shutdown(GLFWwindow* window);
