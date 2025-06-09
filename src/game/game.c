#include <game/game.h>
#include <math/mat4.h>
#include <graphics/shader.h>
#include <input/input.h>
#include <stdio.h>
#include <stdlib.h>

int game_run(GLFWwindow* window){
  struct shader shader = shader_create("../shaders/vs.glsl", "../shaders/fs.glsl");

  vec4 vector = {12,11,10,5};

  shader_bind(shader);
  shader_setv4(shader, "testv4", vector);

  mat4 matrix;

  matrix[0][0] = 1;
  matrix[0][1] = 2;
  matrix[0][2] = 1;
  matrix[0][3] = 1;

  matrix[1][0] = 0;
  matrix[1][1] = 1;
  matrix[1][2] = 0;
  matrix[1][3] = 1;


  matrix[2][0] = 2;
  matrix[2][1] = 3;
  matrix[2][2] = 4;
  matrix[2][3] = 1;

  matrix[3][0] = 1;
  matrix[3][1] = 1;
  matrix[3][2] = 1;
  matrix[3][3] = 1;

  mat4_print(matrix);
  printf("--------------\n");

  mat4 matrix2;

  matrix2[0][0] = 2;
  matrix2[0][1] = 5;
  matrix2[0][2] = 1;
  matrix2[0][3] = 1;

  matrix2[1][0] = 6;
  matrix2[1][1] = 7;
  matrix2[1][2] = 1;
  matrix2[1][3] = 1;

  matrix2[2][0] = 1;
  matrix2[2][1] = 8;
  matrix2[2][2] = 1;
  matrix2[2][3] = 1;

  matrix2[3][0] = 1;
  matrix2[3][1] = 1;
  matrix2[3][2] = 1;
  matrix2[3][3] = 1;

  mat4_print(matrix2);
  printf("--------------\n");

  mat4 result;
  printf("--------------\n");

  mat4_mult(result, matrix, matrix2);
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


