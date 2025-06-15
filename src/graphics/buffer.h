#pragma once

#include <glad/gl.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

uint32_t vao_create();
void vao_bind(uint32_t vao);
void vao_attrib(uint32_t vao, uint32_t vbo, GLuint index, GLint size
,GLenum type, GLboolean normalized, GLsizei stride,void* offset);

uint32_t vbo_create();
void vbo_bind(uint32_t vbo);
void vbo_buffer(size_t size, const void* data, GLenum usage);

uint32_t ibo_create();
void ibo_bind(uint32_t inb);
void ibo_buffer(size_t size, const void* data, GLenum usage);
