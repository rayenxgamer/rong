#pragma once

#include "math/vec4.h"
#include <stdio.h>
#include <stdbool.h>

typedef struct {
  float x, y;
  float xh, yw;
} AABB;

static inline bool aabb_check_collision(float obj1x, float obj1y, float obj1w, float obj1h,
                                        float obj2x, float obj2y, float obj2w, float obj2h){
  if (obj1x < obj2x + obj2w &&
      obj1x + obj1w > obj2x){
    printf("aligned on the X\n");
     if(obj1y < obj2y + obj2h &&
        obj1y + obj1h > obj2y){

      return true;
      }
  }
  return false;
};


/* this one is passed as vectors for convenience instead,
 * it goes:
 * vec4.x = object x
 * vec4.y = object y
 * vec4.z = object width
 * vec4.w = object height*/
static inline bool aabb_check_collisionv4(vec4 obj1attris, vec4 obj2attris){
  if (obj1attris[0] < obj2attris[0] + obj2attris[2] &&
      obj1attris[0] + obj1attris[2] > obj2attris[0] &&
      obj1attris[1] < obj2attris[1] + obj2attris[3] &&
      obj1attris[1] + obj1attris[3] > obj2attris[1]) {
    return true;
  }
  return false;
};

