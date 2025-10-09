#pragma once

#include <graphics/shader.h>
#include <GLFW/glfw3.h>

typedef enum {
  CAMERA_ORTHOGRAPHIC,
  CAMERA_PRESPECTIVE,
} Camera_Type;

typedef struct {
  float x, y, z;
  mat4 view_matrix;
  mat4 projection_matrix;
  float left, right, bottom, top, near, far;
  Camera_Type type;
} Camera;

Camera camera_init(Camera_Type cam_type, vec3 pos, float left, float right, float bottom, float top, float near, float far);
void camera_update(Camera camera, Shader* shader);
void rengine_compute_ortho(mat4 matrix, float left, float right, float bottom, float top, float near, float far);
