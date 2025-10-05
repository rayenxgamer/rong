#pragma once

#include <stdio.h>

typedef float REN_BOOL;

#define REN_TRUE 1
#define REN_FALSE 0
#define LOG_F(f,x) printf(f,x)
#define LOG(x) printf(x)

static inline void ALOG(int x, const char* r){
  if(!x)
    printf("%s",r);
}
