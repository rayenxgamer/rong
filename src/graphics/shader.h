#pragma once

#include <glad/gl.h>
#include <math/vec3.h>
#include <math/vec4.h>
#include <math/mat4.h>
#include <math/mat3.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <stdbool.h>

typedef struct{
  uint32_t handle;
  uint32_t fs_handle;
  uint32_t vs_handle;
} Shader;

void shader_create(Shader* self,const char *vpath, const char *fpath);
static uint32_t shader_compile(const char* shaderpath, GLenum type);
static uint32_t shader_checkerrors(uint32_t handle);

void shader_bind(Shader shader);
void shader_setb(Shader shader, const char* name, bool value);
void shader_seti(Shader shader, const char* name, int value);
void shader_setui(Shader shader, const char* name, uint32_t value);
void shader_setf(Shader shader, const char* name, float value);
void shader_setv4(Shader shader, const char* name, vec4 value);
void shader_setf3(Shader shader, const char* name, float value1, float value2, float value3);
void shader_setv3(Shader shader, const char* name, vec3 value);
void shader_setm4x4(Shader shader, const char* name, mat4 value);
void shader_setm3x3(Shader shader, const char* name, mat3 value);
