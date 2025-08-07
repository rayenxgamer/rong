#include "graphics/shader.h"
#include "math/mat4.h"
#include <math/projection.h>
#include <graphics/camera.h>

struct ortho_camera camera_init_ortho(vec3 pos, float left, float right, float bottom, float top, float near, float far){
  struct ortho_camera temp_camera = {.x = pos[0], .y = pos[1], 0.0f};
  temp_camera.left = left;
  temp_camera.right = right;
  temp_camera.bottom = bottom;
  temp_camera.top = top;
  temp_camera.near = near;
  temp_camera.far = far;

  mat4_identity(temp_camera.view_matrix);

  rengine_math_ortho(temp_camera.projection_matrix, left, right, bottom, top , near, far);

  return temp_camera;
};

void camera_update(struct ortho_camera camera, struct shader* shader){
  shader_bind(*shader);
  shader_setm4x4(*shader, "projection", camera.projection_matrix);
  shader_setm4x4(*shader, "view", camera.view_matrix);
}
