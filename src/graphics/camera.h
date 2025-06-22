#pragma once

#include <graphics/shader.h>
#include <GLFW/glfw3.h>
#include <string.h>

struct camera {
  float x, y, z;
  mat4 view_matrix;
  mat4 projection_matrix;
};

struct camera camera_init_ortho(vec3 pos, float window_width, float window_height, float far);
void camera_update(struct camera camera);

void camera_set_projection_ortho(mat4 dest, float const width, float const height, float const far);
