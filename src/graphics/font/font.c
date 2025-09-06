#include "font.h"
#include <stdio.h>

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
  memcpy(&temp_font_.font_template_buffer_internal, &font_buffer_template, sizeof(char*));
  temp_font_.font_color = (Color){0.0f, 0.0f, 0.0f, 0.0f};

  return temp_font_;
};

void font_draw_one_letter(Font font, char letter, float x, float y, uint8_t size_x, uint8_t size_y, Shader* shader){
  vec2 index;
  isletterinbuffermulti_gi(letter, FONT_MAX_HEIGHT, FONT_MAX_WIDTH ,font.font_template_buffer_internal, index);
  printf("index : %f \t %f\n", index[0], index[1]);
  assert(index != NULL);

  vec4 position;
  vec4_copy(position ,atlas_get_texture_at(&font.font_atlas, index[0], index[1]));
  struct rect font_atlas_rect = renderer_initatlas(font.font_atlas, position,
                                    x, y, 50, 50);

  glUseProgram(shader->handle);
  renderer_drawfromatlas(font.font_atlas, &font_atlas_rect, shader);
};

void font_draw_word(const char* input, Color color, Shader shader){

};
