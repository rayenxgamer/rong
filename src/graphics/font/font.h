#pragma once

#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "glad/gl.h"
#include "utils/string.h"
#include "graphics/atlas/atlas.h"
#include "graphics/defines/colors.h"
#include "graphics/renderer.h"
#include "graphics/shader.h"
#include "math/vec4.h"

#define FONT_MAX_HEIGHT 16
#define FONT_MAX_WIDTH 16

typedef struct {
  Atlas font_atlas;
  Color font_color;
  char font_template_buffer_internal[FONT_MAX_HEIGHT][FONT_MAX_WIDTH];
} Font;
//*
// array[x][y] {
//    "ABCDEFG...P",
//    "QRTSUVXWYZ#####"
// }
//
//*/
//
Font font_init(Atlas* font_atlas, const char font_buffer_template[FONT_MAX_HEIGHT][FONT_MAX_WIDTH]);
void font_draw_one_letter(Font font, char letter, float x, float y, uint8_t size_x, uint8_t size_y, Shader* shader);
void font_draw_word(const char* input, Color color, Shader shader);
