#pragma once

#include <stdio.h>

typedef float vec3[3];

static inline void vec3_add(vec3 dest, vec3 const a, vec3 const b){
  dest[0] = a[0] + b[0];
  dest[1] = a[1] + b[1];
  dest[2] = a[2] + b[2];
};

static inline void vec3_sub(vec3 dest, vec3 const a, vec3 const b){
  dest[0] = a[0] - b[0];
  dest[1] = a[1] - b[1];
  dest[2] = a[2] - b[2];
};

static inline void vec3_multf(vec3 dest, vec3 const a, float const scalar){
  dest[0] = a[0] * scalar;
  dest[1] = a[1] * scalar;
  dest[2] = a[2] * scalar;
};

static inline void vec3_multv(vec3 dest, vec3 const a, vec3 const b){
  dest[0] = a[0] * b[0];
  dest[1] = a[1] * b[1];
  dest[2] = a[2] * b[2];
};

static inline void vec3_copy(vec3 dest, vec3 const a){
  dest[0] = a[0];
  dest[1] = a[1];
  dest[2] = a[2];
};

static inline void vec3_dot(float dest, vec3 const a, vec3 const b){
  dest = (a[0] * b[0]) + (a[1] * b[1]) + (a[2] * b[2]);
};

static inline void vec3_cross(vec3 dest, vec3 const a, vec3 const b){
  dest[0] = a[1]*b[2] - a[2]*b[1];
  dest[1] = a[2]*b[0] - a[0]*b[2];
  dest[2] = a[0]*b[1] - a[1]*b[0];
};

static inline void vec3_print(vec3 vector){
  for (int i = 0; i < 2; i++) {
    printf("%f\n", vector[i]);
  };
};
