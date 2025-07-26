#pragma once

#include "math/vec2.h"
#include "graphics/renderer.h"
#include "graphics/shader.h"
#include "graphics/defines/colors.h"

#define PARTICLE_LIST_MAX_COUNT 10

struct particle {
  struct rect particle_rectangle;
  color color;
  float size_start, size_end;
  float lifetime, lifetime_left;
  vec2 velocity, velocity_change;
  Texture texture;
};

struct particle_list_node {
  struct particle data;
  struct particle_list_node* next;
};

struct particle_list_node* particle_list_node_add_node_end(struct particle_list_node* head, struct particle value);

unsigned int particle_list_get_size(struct particle_list_node* head);

struct particle_list_node* particle_list_node_delete_middle(struct particle_list_node* head, struct particle_list_node* deleted_particle_list_node);
void particle_emit_(struct particle* particle, struct shader* shader);
void particles_emit(struct particle_list_node* head,struct shader* shader);
void particles_update(struct particle_list_node* head, struct shader* shader);
