#include <game/game.h>
#include <graphics/shader.h>
#include <math/mat4.h>
#include <input/input.h>
#include <stdio.h>
#include <stdlib.h>

int game_run(GLFWwindow* window){
  struct shader shader = shader_create("../shaders/vs.glsl", "../shaders/fs.glsl");
  vec4 vector = {12,11,10,5};
  shader_bind(shader);
  shader_setv4(shader, "testv4", vector);
  mat4 matrix;
  mat4_identity(matrix);
  mat4_print(matrix);
  printf("--------------\n");
  mat4 matrix2;
  mat4_identity(matrix2);
  mat4_print(matrix2);
  printf("--------------\n");
  mat4 result;
  mat4_add(result, matrix, matrix2);
  mat4_print(result);
  printf("--------------\n");


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


