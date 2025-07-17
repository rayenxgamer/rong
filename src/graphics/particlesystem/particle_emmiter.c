#include "particle_emmiter.h"

void particle_emit(struct particle* particle, struct shader* shader){
  if (particle->lifetime > 0.0f) {
    renderer_drawrect_noinit(&particle->particle_rectangle, particle->color, shader);
  }else{
    return;
  }
};

void particles_update(){
  // TODO: some way to loop through all of the particles with more than 0 lifetime and emit them
  // {also to not draw them when they don't have more than 0 lifetime and remove them}
};

/* TODO: actually build a particle emmiting system?? */
