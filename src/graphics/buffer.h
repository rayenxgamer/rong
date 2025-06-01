#pragma once

#include <glad/gl.h>
#include <stdint.h>

uint32_t vao_create(uint32_t* vao);
void vao_bind(uint32_t* vao);

uint32_t vbo_create(uint32_t* vbo);
void vbo_bind(uint32_t* vbo);

uint32_t inb_create(uint32_t* inb);
void inb_bind(uint32_t* inb);
