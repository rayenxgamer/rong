#pragma once

#include <math.h>
#include <math/vec2.h>
#include <math/vec3.h>
#include <stdlib.h>

#define PI 3.14159265358979323846

#define MIN(i, j) (((i) < (j)) ? (i) : (j))
#define MAX(i, j) (((i) > (j)) ? (i) : (j))
#define RANDMAXMIN(i, j) rand() % (i + 1 - j) + j

static inline int rand_range(int minimum, int maximum)
{
    int diff = minimum-maximum;
    return (int) (((double)(diff+1)/RAND_MAX) * rand() + minimum);
}

static inline float magnitudev2 (vec2 a){
  return sqrtf(powf(a[0], 2) + powf(a[1], 2));
};

static inline void normalizev2(vec2 target,vec2 a){
  float magnitude_of_a = magnitudev2(a);
  a[0] = a[0] / magnitude_of_a;
  a[1] = a[1] / magnitude_of_a;
};

static inline float magnitudev3 (vec3 a){
  return sqrtf(powf(a[0], 2) + powf(a[1], 2) + powf(a[2], 2));
};

static inline void normalizev3(vec3 target,vec3 a){
  float magnitude_of_a = magnitudev3(a);
  for (int i = 0; i < 2; ++i) {
    a[i] /= magnitude_of_a;
  }
};

/* static inline float random_max_min(float max, float min){
  float random = (float)rand();
  return random % (max + 1.0f - min) + min;
}; */

static inline float distance3v(vec3 a, vec3 b){
  return sqrtf((powf(b[0] - a[0], 2)) + powf(b[1] - a[1], 2) + powf(b[2] - a[2], 2));
};

static inline float distance2v(vec2 a, vec2 b){
  return sqrtf((powf(b[0] - a[0], 2)) + powf(b[1] - a[1], 2) + 0.0f);
};

static inline void clampf(float* num, float min ,float max){
  (*num > max) ? (*num = max) : (*num = *num);
  (*num < min) ? (*num = min) : (*num = *num);
};

static inline void clampfmax(float num, float max){
  (num >= max) ? (num = max) : (num = num);
};

static inline float deg_to_rad(float deg){
  return deg * PI / 180;
};

static inline float rad_to_deg(float rad){
  return rad * 180 / PI;
};
