#include "particle_emmiter.h"
#include "graphics/renderer.h"
#include "math/common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int particle_list_get_size(struct particle_list_node* head){
  int count = 0;
  struct particle_list_node* curr = head;
  while (curr) {
      count++;
    if (curr->next) {
      curr = curr->next;
    }else{
      break;
    }
  }
  return count;
}

struct particle_list_node* particle_list_node_add_node_end(struct particle_list_node* head, struct particle value){
  struct particle_list_node* temp_particle_list_node = NULL;
  temp_particle_list_node = malloc(sizeof(struct particle_list_node));
  temp_particle_list_node->data = value;
  temp_particle_list_node->next = NULL;
  while (head->next != NULL) {
    head = head->next;
  }
  head->next = temp_particle_list_node;
  return head->next;
};

struct particle_list_node* particle_list_node_delete_from_start(struct particle_list_node *head){
    if (head == NULL)
      return NULL;

    struct particle_list_node* temp = head;
    head = head->next;

    free(temp);

    return head;
};

struct particle_list_node* particle_list_node_delete_middle(struct particle_list_node *head, struct particle_list_node *deleted_particle_list_node){
  if (head == NULL) {
    return NULL;
  }

  if (memcmp(head, deleted_particle_list_node, sizeof(struct particle_list_node)) == 0) {
    memmove(head, deleted_particle_list_node->next, sizeof(struct particle_list_node));
    free(deleted_particle_list_node);
    return head;
  }

  while (head->next != NULL) {
    if (memcmp(head->next, deleted_particle_list_node, sizeof(struct particle_list_node)) == 0){
      head->next = deleted_particle_list_node->next;
      free(deleted_particle_list_node);
      return head;
    }else{
      head = head->next;
    }
  }
  return head;
};

void particles_emit(struct particle_list_node* head,struct shader* shader){
  if (particle_list_get_size(head) < PARTICLE_LIST_MAX_COUNT) {
    struct particle_list_node* new_node = NULL;
    new_node = malloc(sizeof(struct particle_list_node));
    memcpy(&new_node->data, &head->data, sizeof(struct particle));
    new_node->next = NULL;
    while (head->next != NULL) {
      head = head->next;
    }
    head->next = new_node;
  }
}

void particle_emit_(struct particle* particle, struct shader* shader){
  if (particle->lifetime > 0.0f) {
    renderer_drawrect_particle(&particle->particle_rectangle, particle->color,shader);
    particle->color.a -= 0.04f;
    particle->lifetime -= 0.06f;
  }else{
    return;
  }
};

void particles_update(struct particle_list_node* head, struct shader* shader){
  // TODO: some way to loop through all of the particles with more than 0 lifetime and emit them
  // {also to not draw them when they don't have more than 0 lifetime and remove them}
  while (head->next != NULL && particle_list_get_size(head) <= PARTICLE_LIST_MAX_COUNT) {
    if (head->next->data.lifetime < 0) {
      head = particle_list_node_delete_middle(head, head->next);
    }
    particle_emit_(&head->data, shader);
    head = head->next;
  }
};

/* TODO: actually build a particle emmiting system?? */
