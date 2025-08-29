#pragma once

#include <stdio.h>
#include <assert.h>

#define LOG(x) printf(x)
// #define ALOG(x, r) if (!x) printf(r)

static inline void ALOG(int x, const char* r){
  if(!x)
    printf("%s",r);
}
