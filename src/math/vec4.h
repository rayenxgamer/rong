#pragma once

#include <stdio.h>

typedef float vec4[4];

static inline void vec4_add(vec4 dest, vec4 const a, vec4 const b){
  dest[0] = a[0] + b[0];
  dest[1] = a[1] + b[1];
  dest[2] = a[2] + b[2];
  dest[3] = a[3] + b[3];
};

static inline void vec4_sub(vec4 dest, vec4 const a, vec4 const b){
  dest[0] = a[0] - b[0];
  dest[1] = a[1] - b[1];
  dest[2] = a[2] - b[2];
  dest[3] = a[3] - b[3];
};

static inline void vec4_dupl(vec4 dest, vec4 vector){
  dest[0] = vector[0];
  dest[1] = vector[1];
  dest[2] = vector[2];
  dest[3] = vector[3];
};

static inline void vec4_multf(vec4 dest, vec4 const a, float const scalar){
  dest[0] = a[0] * scalar;
  dest[1] = a[1] * scalar;
  dest[2] = a[2] * scalar;
  dest[3] = a[3] * scalar;
};

static inline void vec4_multv(vec4 dest, vec4 const a, vec4 const b){
  dest[0] = a[0] * b[0];
  dest[1] = a[1] * b[1];
  dest[2] = a[2] * b[2];
  dest[3] = a[3] * b[3];
};

static inline void vec4_copy(vec4 dest, vec4 const a){
  dest[0] = a[0];
  dest[1] = a[1];
  dest[2] = a[2];
  dest[3] = a[3];
};

static inline void vec4_dot(float dest, vec4 const a, vec4 const b){
  dest = (a[0] * b[0]) + (a[1] * b[1]) + (a[2] * b[2]) + (a[3] * b[3]);
};

static inline void vec4_print(vec4 vector){
  for (int i = 0; i < 4; i++) {
    printf("%f\n", vector[i]);
  };
};
