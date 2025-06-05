#pragma once

#include <math/vec4.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

static inline void mat4_print(mat4 matrix){
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      printf("%d", (int)matrix[i][j]);
    }
    printf("\n");
  }
};
