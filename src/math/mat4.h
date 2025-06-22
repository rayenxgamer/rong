#pragma once

#include <math/vec4.h>
#include <math/vec3.h>
#include <math.h>
#include <stdio.h>

typedef vec4 mat4[4];

static inline void mat4_identity(mat4 dest){
  for (int i = 0;i < 4 ; i++) {
    for (int j = 0; j < 4; j++) {
      if (i == j) {
        dest[i][j] = 1.0f;
      }else{
        dest[i][j] = 0.0f;
      }
    }
  }
};

static inline void mat4_zero(mat4 matrix){
  for (int i = 0;i < 4 ; i++) {
    for (int j = 0; j < 4; j++) {
      matrix[i][j] = 0.0f;
    }
  }
};

static inline void mat4_dupl(mat4 dest, mat4 matrix){
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      dest[i][j] = matrix[i][j];
    }
  }
};

/*doing this manually might be faster, ill test that sometime
 also this was copied from linmath and modified to fit here */

static inline void mat4_mult(mat4 dest, mat4 a, mat4 b){
	int k, r, c;
  mat4 temp_matrix;
	for(c = 0; c < 4; c++){
    for(r = 0; r < 4; r++) {
      temp_matrix[c][r] = 0.0f;
      for(k = 0; k < 4; k++){
        temp_matrix[c][r] += (a[c][k] * b[k][r]);
      }
    }
  }
  mat4_dupl(dest, temp_matrix);
};

static inline void mat4_multv(vec4 dest, mat4 const matrix, vec4 const vector){
  vec4 temp_vector4;
	int i, j;
	for(i = 0; i < 4; i++){
    temp_vector4[i] = 0.0f;
    for(j = 0; j < 4; j++) {
      temp_vector4[i] += matrix[i][j] * vector[j];
    }
  }
  vec4_dupl(dest, temp_vector4);
};

static inline void mat4_add(mat4 dest, mat4 const a, mat4 const b){
  for (int i = 0;i < 4;i++) {
    for (int j = 0; j < 4; j++) {
      dest[i][j] = a[i][j] + b[i][j];
    }
  }
};

static inline void mat4_sub(mat4 dest, mat4 const a, mat4 const b){
  for (int i = 0;i < 4;i++) {
    for (int j = 0; j < 4; j++) {
      dest[i][j] = a[i][j] - b[i][j];
    }
  }
};

static inline void mat4_scalef(mat4 matrix, float scale){
  mat4 temp_matrix = { {scale, 0.0f, 0.0f,0.0f},
                       {0.0f, scale, 0.0f, 0.0f},
                       {0.0f, 0.0f, scale, 0.0f},
                       {0.0f, 0.0f, 0.0f, 1.0f} };
  mat4_mult(matrix, matrix, temp_matrix);
}

static inline void mat4_scalevf(mat4 matrix,  float x, float y, float z){
  mat4 temp_matrix = { {x, 0.0f, 0.0f,0.0f},
                       {0.0f, y, 0.0f, 0.0f},
                       {0.0f, 0.0f, z, 0.0f},
                       {0.0f, 0.0f, 0.0f, 1.0f} };
  mat4_mult(matrix, matrix, temp_matrix);
}

static inline void mat4_scalev(mat4 matrix, vec3 scale_vector){
  mat4 temp_matrix = { {scale_vector[0], 0.0f, 0.0f,0.0f},
                       {0.0f, scale_vector[1], 0.0f, 0.0f},
                       {0.0f, 0.0f, scale_vector[2], 0.0f},
                       {0.0f, 0.0f, 0.0f, 1.0f} };
  mat4_mult(matrix, matrix, temp_matrix);
}

static inline void mat4_scale_make(mat4 matrix, float scale){
  mat4_identity(matrix);
  for (int i = 0; i < 2; i++) {
    matrix[i][i] = scale;
  }
}

static inline void mat4_scalev_make(mat4 matrix, vec3 scale_vector){
  matrix[0][0] = scale_vector[0];
  matrix[1][1] = scale_vector[1];
  matrix[2][2] = scale_vector[2];
}

static inline void mat4_rotate(mat4 matrix, float angle, vec3 rotation_axis){
  float cos_theta = cosf(angle);
  float sin_theta = sinf(angle);
  mat4 temp_matrix;
  mat4_identity(temp_matrix);
  if (rotation_axis[0] == 1.0f) {
    temp_matrix[1][1] = cos_theta;
    temp_matrix[1][2] = -sin_theta;

    temp_matrix[2][1] = sin_theta;
    temp_matrix[2][2] = cos_theta;

  } else if (rotation_axis[1] == 1.0f) {
    temp_matrix[0][0] = cos_theta;
    temp_matrix[0][2] = sin_theta;

    temp_matrix[2][0] = -sin_theta;
    temp_matrix[2][2] = cos_theta;
  }else if (rotation_axis[2] == 1.0f){
    temp_matrix[0][0] = cos_theta;
    temp_matrix[0][1] = -sin_theta;

    temp_matrix[1][0] = sin_theta;
    temp_matrix[1][1] = cos_theta;
  }
  else{
    fprintf(stderr, "mat4 cannot be rotated on zero axis!\n");
    return;
  };

  mat4_mult(matrix, matrix, temp_matrix);
};

static inline void mat4_translate(mat4 matrix, vec3 vec){
  mat4 temp_matrix;
  mat4_identity(temp_matrix);
  temp_matrix[3][0] = vec[0];
  temp_matrix[3][1] = vec[1];
  temp_matrix[3][2] = vec[2];
  mat4_mult(matrix, matrix, temp_matrix);
};

static inline void mat4_translatevf(mat4 matrix, float x, float y, float z){
  mat4 temp_matrix;
  mat4_identity(temp_matrix);
  temp_matrix[3][0] = x;
  temp_matrix[3][1] = y;
  temp_matrix[3][2] = z;
  mat4_mult(matrix, matrix, temp_matrix);
};

static inline void mat4_translate_make(mat4 matrix, vec3 vec){
  matrix[3][0] = vec[0];
  matrix[3][1] = vec[1];
  matrix[3][2] = vec[2];
};

static inline void mat4_print(mat4 matrix){
  printf("---------------");
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      printf("%d", (int)matrix[i][j]);
    }
    printf("\n");
  }
  printf("---------------");
};
