#include "font.h"
#include "math/vec2.h"
#include <stdio.h>
#include <string.h>

Font font_init(Atlas* font_atlas, const char font_buffer_template[FONT_MAX_HEIGHT][FONT_MAX_WIDTH]){
  Font temp_font_;

  // const char a[100][100] = {
  //   "hello world lakjwdklajwkldjkl",
  //   "hello"
  // };
  //
  // char b[100][100];
  //
  // memcpy(&b, &a, sizeof(char*));
  // LOGS(b[0][4]);


  temp_font_.font_atlas = *font_atlas;
  temp_font_.font_color = (Color){0.0f, 0.0f, 0.0f, 0.0f};
  return temp_font_;
};

void font_draw_one_letter(Font* font, char letter, float x, float y, uint8_t width, uint8_t height, Shader* shader){

  char font_buffer[FONT_MAX_HEIGHT][FONT_MAX_WIDTH] = {
    "abcdefghijklmnop",
    "qrstuvwxyz",
    "1234567890",
    ".?:;-=()[]!",
  };

  vec2 index;
  isletterinbuffermulti_gi(letter, FONT_MAX_HEIGHT, FONT_MAX_WIDTH , font_buffer, index);

  vec4 position;
  vec4_copy(position ,atlas_get_texture_at(&font->font_atlas, index[1], index[0]));
  struct rect font_atlas_rect = renderer_initatlas(font->font_atlas, position,
                                    x, y, height, width);

  glUseProgram(shader->handle);
  renderer_drawfromatlas(font->font_atlas, &font_atlas_rect, shader);
};

void font_draw_word(Font* font ,const char* input, float x, float y, float width, float height, Color color, float offset, Shader* shader){
  uint32_t i = 0;
  float last_offset = x;

  while (i < strlen(input)) {
    font_draw_one_letter(font, input[i], last_offset, y, width, height, shader);
    last_offset += offset;
    i++;
  }
};
