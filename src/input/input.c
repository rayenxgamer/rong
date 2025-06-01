#include <input/input.h>

void input_update(GLFWwindow* window){
};

int input_isKeyPressed(GLFWwindow* window, int key){
  if (glfwGetKey(window, key) == GLFW_PRESS) {
    return 1;
  }else{
    return 0;
  }
};

int input_isKeyHeld(GLFWwindow* window, int key){
  if (glfwGetKey(window, key) == GLFW_REPEAT) {
    return 1;
  }else{
    return 0;
  }
};
