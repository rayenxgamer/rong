#pragma once

#include "math/vec2.h"

#include <assert.h>
#include <string.h>
#include <stdbool.h>

static inline int isletterinbuffer(char letter, const char* buffer){
  assert(buffer != NULL);
  for (unsigned int i = 0; i < strlen(buffer); i++) {
    if (buffer[i] == letter) {
      return i;
    }
  }
  return 0;
}

static inline bool isletterinbuffermulti(char letter, int x, int y, const char buffer[x][y]){
  assert(buffer != NULL);
  for (unsigned int i = 0; i < x; i++) {
    for (unsigned int j = 0; j < y; j++) {
      if (buffer[i][j] == letter) {
        return true;
      }
    }
  }
  return false;
}

static inline bool isletterinbuffermulti_gi(char letter, int x, int y, const char buffer[x][y], vec2 output){
  assert(buffer != NULL);
  assert(output != NULL);

  for (unsigned int i = 0; i < x; i++) {
    for (unsigned int j = 0; j < y; j++) {
      if (buffer[i][j] == letter) {
        vec2_copy(output, (vec2){i, j});
        return true;
      }
    }
  }
  output = NULL;

  return false;
}
