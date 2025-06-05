#pragma once

#include <stdio.h>

typedef float vec2[2];

static inline void vec2_add(vec2 dest, vec2 const a, vec2 const b){
  dest[0] = a[0] + b[0];
  dest[1] = a[1] + b[1];
};

static inline void vec2_sub(vec2 dest, vec2 const a, vec2 const b){
  dest[0] = a[0] - b[0];
  dest[1] = a[1] - b[1];
};

static inline void vec2_multf(vec2 dest, vec2 const a, float const scalar){
  dest[0] = a[0] * scalar;
  dest[1] = a[1] * scalar;
};

static inline void vec2_multv(vec2 dest, vec2 const a, vec2 const b){
  dest[0] = a[0] * b[0];
  dest[1] = a[1] * b[1];
};

static inline void vec2_copy(vec2 dest, vec2 const a){
  dest[0] = a[0];
  dest[1] = a[1];
};

static inline void vec2_dot(float dest, vec2 const a, vec2 const b){
  dest = (a[1] * b[0]) + (a[1] * b[1]);
};

static inline void vec2_print(vec2 vector){
  for (int i = 0; i < 1; i++) {
    printf("%f\n", vector[i]);
  };
};
