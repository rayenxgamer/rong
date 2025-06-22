#pragma once

#include <math/mat4.h>
#include <string.h>

/* transforms mat4 matrix into an orthographic matrix (no multiplication)
 * right handed GL convention style
 * NOTE: LH is pretty hard for me to understand right now!
 * */
static inline void rengine_math_ortho(mat4 matrix, float left, float right, float bottom, float top, float near, float far){
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


