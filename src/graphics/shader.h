#pragma once

#include <glad/gl.h>
#include <math/vec3.h>
#include <math/vec4.h>
#include <math/mat4.h>
#include <math/mat3.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

struct shader{
  uint32_t handle;
  uint32_t fs_handle;
  uint32_t vs_handle;
};

struct shader shader_create(const char* vpath, const char* fpath);
static uint32_t shader_compile(const char* shaderpath, GLenum type);
static uint32_t shader_checkerrors(uint32_t handle);

void shader_bind(struct shader shader);
void shader_setb(struct shader shader, const char* name, bool value);
void shader_seti(struct shader shader, const char* name, int value);
void shader_setui(struct shader shader, const char* name, uint32_t value);
void shader_setf(struct shader shader, const char* name, float value);
void shader_setv4(struct shader shader, const char* name, vec4 value);
void shader_setv3(struct shader shader, const char* name, vec3 value);
void shader_setm4x4(struct shader shader, const char* name, mat4 value);
void shader_setm3x3(struct shader shader, const char* name, mat3 value);
