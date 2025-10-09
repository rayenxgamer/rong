#include "math/mat4.h"
#include "graphics/shader.h"

#include <graphics/camera.h>
#include <stdio.h>

Camera camera_init(Camera_Type cam_type, vec3 pos, float left, float right, float bottom, float top, float near, float far){
  Camera temp_camera = {
    .x = pos[0],
    .y = pos[1],
    .z = 0.0f,
    .left = left,
    .right = right,
    .bottom = bottom,
    .top = top,
    .near = near,
    .far = far,
    .type = cam_type,
  };

  mat4_identity(temp_camera.view_matrix);

  switch (cam_type) {
    case CAMERA_ORTHOGRAPHIC:
      rengine_compute_ortho(temp_camera.projection_matrix, left, right, bottom, top , near, far);
      break;
    case CAMERA_PRESPECTIVE:
      // prespective cam setup, not needed for this project
      break;
    default:
      fprintf(stderr, "choose a proper camrea type, either CAMERA_ORTHOGRAPHIC or CAMERA_PRESPECTIVE!");
      fprintf(stderr, "you chose %d!", cam_type);
      break;
  }


  return temp_camera;
};

void rengine_compute_ortho(mat4 matrix, float left, float right, float bottom, float top, float near, float far){
  mat4 temp_matrix;
  mat4_zero(temp_matrix);

  temp_matrix[0][0] = 2.0f / (right - left);
  temp_matrix[1][1] = 2.0f / (top - bottom);
  temp_matrix[2][2] = 2.0f / (near - far);
  temp_matrix[3][3] = 1.0f;

  temp_matrix[3][0] = (left + right) / (left - right);
  temp_matrix[3][1] = (bottom + top) / (bottom - top);
  temp_matrix[3][2] = (near + far) / (near - far);

  memcpy(matrix, temp_matrix, sizeof(mat4));
};

void camera_update(Camera camera, Shader* shader){
  shader_bind(*shader);
  shader_setm4x4(*shader, "projection", camera.projection_matrix);
  shader_setm4x4(*shader, "view", camera.view_matrix);
}
