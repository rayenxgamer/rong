#pragma once

#include <math/vec3.h>
#include <stdio.h>

typedef vec3 mat3[3];

static inline void mat3_identity(mat3 dest){
  for (int i = 0;i < 3 ; i++) {
    for (int j = 0; j < 3; j++) {
      if (i == j) {
        dest[i][j] = 1.0f;
      }else{
        dest[i][j] = 0.0f;
      }
    }
  }
};

/*doing this manually might be faster, ill test that sometime
 also this was copied from linmath and modified to fit here */

static inline void mat3_mult(mat3 dest, mat3 const a, mat3 const b){
	int k, r, c;
	for(c = 0; c < 3; c++){
    for(r = 0; r < 3; r++) {
		dest[c][r] = 0.0f;
      for(k = 0; k < 3; k++)
        dest[c][r] += a[c][k] * b[k][r];
      }
    }
};

static inline void mat3_add(mat3 dest, mat3 const a, mat3 const b){
  for (int i = 0;i < 3;i++) {
    for (int j = 0; j < 3; j++) {
      dest[i][j] = a[i][j] + b[i][j];
    }
  }
};

static inline void mat3_sub(mat3 dest, mat3 const a, mat3 const b){
  for (int i = 0;i < 3;i++) {
    for (int j = 0; j < 3; j++) {
      dest[i][j] = a[i][j] - b[i][j];
    }
  }
};

static inline void mat3_print(mat3 matrix){
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      printf("%d", (int)matrix[i][j]);
    }
    printf("\n");
  }
};


