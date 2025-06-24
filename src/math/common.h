#pragma once

#include <stdio.h>
#define PI 3.14159265358979323846

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
