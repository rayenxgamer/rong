#include "math/mat4.h"
#include <math/projection.h>
#include <graphics/camera.h>

struct camera camera_init_ortho(vec3 pos, float window_width, float window_height, float far){
  struct camera temp_camera = {.x = pos[0], .y = pos[1], 0.0f};
  mat4 temp_view_matrix;
  mat4_identity(temp_view_matrix);
  mat4_translate(temp_view_matrix, (vec3){-temp_camera.x, -temp_camera.y, 0.0f});
  memcpy(temp_camera.view_matrix, temp_view_matrix, sizeof(mat4));

  camera_set_projection_ortho(temp_camera.projection_matrix, window_width, window_height, far);

  return temp_camera;
};

void camera_update(struct camera camera){
  // TODO:
}

void camera_set_projection_ortho(mat4 dest, float const width, float const height, float const far)
{
  mat4 temp_matrix;
  rengine_math_ortho(temp_matrix, 0.0f, width, height, 0.0f , -1.0f, far);
  memcpy(dest, temp_matrix, sizeof(mat4));
};


