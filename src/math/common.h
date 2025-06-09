#pragma once

#include <stdio.h>

#define PI 3.14159265358979323846

static inline float deg_to_rad(float deg){
  return deg * PI / 180;
};

static inline float rad_to_deg(float rad){
  return rad * 180 / PI;
};
