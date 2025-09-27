#pragma once

#include <stdint.h>

#include "graphics/atlas/atlas.h"
#include "graphics/defines/colors.h"
#include "graphics/shader.h"

#define FONT_MAX_HEIGHT 16
#define FONT_MAX_WIDTH 16

typedef struct {
  Atlas font_atlas;
  Color font_color;
  char font_template_buffer_internal[FONT_MAX_HEIGHT][FONT_MAX_WIDTH];
} Font;

Font font_init(Atlas* font_atlas, const char font_buffer_template[FONT_MAX_HEIGHT][FONT_MAX_WIDTH]);
void font_draw_one_letter(Font* font, char letter, float x, float y, uint8_t size_x, uint8_t size_y, Shader* shader);

void font_draw_one_letter_color(Font* font, char letter, float x, float y, uint8_t width, uint8_t height, Color color, Shader* shader);

void font_draw_word_color_single(Font* font ,const char* input, float x, float y, float width, float height
                          , Color color, float offset, Shader* shader);
void font_draw_word_color(Font* font ,const char* input, float x, float y, float width, float height,
                          int buffer_size ,Color color_buffer[buffer_size], float offset, Shader* shader);

void font_draw_word(Font* font, const char* input, float x, float y, float height, float width, Color color, float offset, Shader* shader);
