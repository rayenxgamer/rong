#pragma once

#include <graphics/shader.h>
#include <GLFW/glfw3.h>

struct ortho_camera {
  float x, y, z;
  mat4 view_matrix;
  mat4 projection_matrix;
  float left, right, bottom, top, near, far;
};

struct ortho_camera camera_init_ortho(vec3 pos, float left, float right, float bottom, float top, float near, float far);
void camera_update(struct ortho_camera camera, Shader* shader);
