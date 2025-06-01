#include <game/window.h>

GLFWwindow* window_init(struct window window){
  if (!glfwInit()){
    printf("failed to init glfw\n");
    glfwTerminate();
    exit(1);
  };

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

  GLFWwindow* win = glfwCreateWindow(window.width, window.height, window.title, NULL, NULL);
  glfwMakeContextCurrent(win);

  if(!gladLoadGL(glfwGetProcAddress)){
    printf("failed to load glad!\n");
    glfwTerminate();
    exit(1);
  };

  return win;
};

void window_shutdown(GLFWwindow* window){
  glfwDestroyWindow(window);
  glfwTerminate();
}


