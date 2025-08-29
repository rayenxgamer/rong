#pragma once

#include <stdio.h>

#include "graphics/atlas/atlas.h"
#include "graphics/defines/colors.h"
#include "graphics/renderer.h"
#include "graphics/shader.h"
#include "math/vec4.h"

typedef struct {
 Atlas font_atlas_;
 color font_color;
} Font;

Font font_init(Atlas font_atlas);
void font_draw_one_letter(Font font);
void font_draw_word(const char* input, color color, struct shader shader);
