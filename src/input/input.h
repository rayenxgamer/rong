#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>

void input_update(GLFWwindow* window);
int input_isKeyPressed(GLFWwindow* window,int key);
int input_isKeyHeld(GLFWwindow* window, int key);
