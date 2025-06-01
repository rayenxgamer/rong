#include <game/game.h>
#include <input/input.h>
#include <stdlib.h>

int game_run(GLFWwindow* window){
  while (!glfwWindowShouldClose(window)) {
    game_update(window);

  }
  return EXIT_SUCCESS;
};

void game_update(GLFWwindow *window){
    glClearColor(0.8f,0.2f,1.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
    glfwPollEvents();
    if (input_isKeyPressed(window, GLFW_KEY_ESCAPE)){
      glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

};


void game_shutdown(GLFWwindow *window){
  printf("shutting down..\n");
}


