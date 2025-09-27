#include <glad/gl.h>

static inline void ENABLE_BLEND_MINUS_ALPHA(){
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
};

static inline void DISBLE_BLEND(){
  glDisable(GL_BLEND);
};
