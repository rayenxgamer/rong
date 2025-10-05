#include "audio/audio.h"
#include "graphics/camera.h"
#include "graphics/defines/colors.h"
#include "graphics/shader.h"
#include "graphics/texture.h"
#include "graphics/renderer.h"
#include "graphics/atlas/atlas.h"
#include "graphics/particlesystem/particle_emmiter.h"
#include "graphics/font/font.h"
#include "math/projection.h"
#include "math/common.h"
#include "math/vec2.h"
#include "game/ball.h"
#include "game/window.h"
#include "utils/general.h"
#include "utils/graphics.h"

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define PLAYER_VERT_SPEED 6.0f
#define GRAVITY -1.0f
#define SOUND_COUNT 1

background_props bprops;

Rect player1, player2, ball_rect;
Rect background_rect;
Shader debugshader;
Shader textureshader;
Shader fontshader;
Shader particleshader;
struct ortho_camera cam;
struct ball ball_properties;
struct particle_list_node* head;
struct particle particle_default;
Atlas font_atlas;
Rect font_atlas_rect;
Texture font_atlas_texture;

Texture loafer, string_ball, twach, bg_texture;
Texture star_particle;
Font game_font;

static Sound sounds[SOUND_COUNT];

static const char* sound_file_paths_buffer[SOUND_COUNT] = {
  "assets/music/temp/music_loop.mp3",
};

// TODO: make this a little more intuitive
vec2 player1_coords;
vec2 player2_coords;

unsigned int total_tick_count = 0;

static void init(){

  ren_audio_init(SOUND_COUNT, sound_file_paths_buffer, sounds);

  vec2_copy(player1_coords, (vec2){590.0f, 180.0f});
  vec2_copy(player2_coords, (vec2){25.0f, 180.0f});

  srand(time(NULL));
  ball_properties.vel[0] = rand_range(-5, 5);
  ball_properties.vel[1] = rand_range(-5, 5);

  cam = camera_init_ortho((vec3){0.0f, 0.0f, 0.0f}, 0.0f, 640.0f, 0.0f, 480.0f, -1.0f, 1.0f);

  bg_texture = tex_create("assets/sprites/level_background_purpur-dreams.png", true);
  loafer = tex_create("assets/sprites/player_loafer.png", true);
  string_ball = tex_create("assets/sprites/string_ball.png", true);
  twach = tex_create("assets/sprites/player_twach.png", true);
  star_particle = tex_create("assets/sprites/star_purple_remastered_firstiteration.png", true);
  font_atlas_texture = tex_create("assets/fonts/font.png", true);

  font_atlas = (Atlas){
    .texture = &font_atlas_texture,
    .size_x_ = 8,
    .size_y_ = 8
  };

  vec4 position;
  vec4_copy(position ,atlas_get_texture_at(&font_atlas, 11, 0));
  font_atlas_rect = renderer_initatlas(font_atlas, position,
                                    300.0f, 240.0f, 50, 50);

  char font_buffer[FONT_MAX_HEIGHT][FONT_MAX_WIDTH] = {
    "abcdefghijklmnop",
    "qrstuvxwyz",
    "1234567890",
    ".?:;-=()[]",
  };

  game_font = font_init(&font_atlas, font_buffer);

  bprops = renderer_initbackground((background_props){480.0f, 640.0f, bg_texture});

  window_set_attributes(640, 480, "RONG: on the RENGINE!");

  vec4_copy(particle_default.color ,(Color){.0, .0, .0, 1.0});
  particle_default.lifetime = 1.0f;

  particle_default.particle_rectangle.x = 320.0f;
  particle_default.particle_rectangle.y = 240.0f;
  particle_default.particle_rectangle.height = 30;
  particle_default.particle_rectangle.width = 30;

  particle_default.particle_rectangle = renderer_initrect_tex(particle_default.particle_rectangle.x,particle_default.particle_rectangle.y,
                                                              particle_default.particle_rectangle.height, particle_default.particle_rectangle.width,
                                                              star_particle);

  head = malloc(sizeof(struct particle_list_node));
  head->data = particle_default;
  head->next = NULL;

  shader_create(&debugshader, "shaders/vs.glsl", "shaders/fs.glsl");
  shader_create(&fontshader, "shaders/fontshader/font_shader_vs.glsl", "shaders/fontshader/font_shader_fs.glsl");
  shader_create(&textureshader, "shaders/textureshaders/vs.glsl", "shaders/textureshaders/fs.glsl");
  shader_create(&particleshader, "shaders/particleshader/vs.glsl", "shaders/particleshader/fs.glsl");

  ball_rect = renderer_initrect_tex(320.0f, 240.0f, 25.0f, 25.0f, string_ball);
  player1 = renderer_initrect_tex(player1_coords[0], player1_coords[1], 120.0f, 25.0f, twach);
  player2 = renderer_initrect_tex(player2_coords[0], player2_coords[1], 120.0f, 25.0f, loafer);

  ball_properties.ball_rectangle = &ball_rect;

  ren_audio_play_volume(&sounds[0], REN_AUDIO_LOOP, .6);
};

static void render(){
  renderer_clear_color(0.0f, 0.0f, 0.0f, 0.0f);

  ENABLE_BLEND_MINUS_ALPHA();
  renderer_drawbackground(&bprops, &textureshader);

  font_draw_one_letter_color(&game_font, 'r', 220, 360, 50, 50, REN_RED, &fontshader);
  font_draw_one_letter_color(&game_font, 'o', 270, 360, 50, 50, REN_BLUE, &fontshader);
  font_draw_one_letter_color(&game_font, 'n', 330, 360, 50, 50, REN_YELLOW_GOLDEN, &fontshader);
  font_draw_one_letter_color(&game_font, 'g', 380, 360, 50, 50, REN_ORANGE_DEV, &fontshader);

  renderer_drawrect_tex(ball_rect, &textureshader);

  particles_update(head, &particleshader);

  renderer_drawrect_tex(player2, &textureshader);
  renderer_drawrect_tex(player1, &textureshader);

  DISBLE_BLEND();
};

static void tick(){
  total_tick_count++;

  if(window_is_pressed(GLFW_KEY_ESCAPE))
    window_set_should_close();

  if (total_tick_count >= 2) {
    particles_emit(head, &textureshader);
    total_tick_count = 0;
  }
};
static void update(float deltatime){
  camera_update(cam, &debugshader);
  camera_update(cam, &textureshader);
  camera_update(cam, &particleshader);
  camera_update(cam, &fontshader);

  rengine_math_ortho(cam.projection_matrix, cam.left, cam.right, cam.bottom, cam.top , cam.near, cam.far);

  if (window_is_pressed(GLFW_KEY_S))
    player1.y -= PLAYER_VERT_SPEED;

  if (window_is_pressed(GLFW_KEY_W))
    player1.y += PLAYER_VERT_SPEED;

  if (window_is_pressed(GLFW_KEY_K))
    player2.y -= PLAYER_VERT_SPEED;

  if (window_is_pressed(GLFW_KEY_I))
    player2.y += PLAYER_VERT_SPEED;

  ball_update(&ball_properties, deltatime);
  ball_do_collisions(&ball_properties, &player1, &player2);

  head->data = particle_default;
  head->data.particle_rectangle.x = ball_properties.ball_rectangle->x;
  head->data.particle_rectangle.y = ball_properties.ball_rectangle->y;

  if (player1.y + player1.height >= 480.0f){
    player1.y = 480.0f - player1.height;
  };
  if(player1.y <= 0.0f){
    player1.y = 0.0f;
  };

  if (player2.y + player2.height >= 480.0f){
    player2.y = 480.0f - player2.height;
  };
  if(player2.y <= 0.0f){
    player2.y = 0.0f;
  };
  int x = 1;
  ALOG(x, "did work");
};

static void shutdown(){
};

int main(int argc, char* argv[]) {
  if (argc == 2) {
    int parameter_count = 2;
    char debug_string[] = "--debug";
    char help_string[] = "--help";
    if (memcmp(argv[1],debug_string, strlen(debug_string)) == 0) {
      #ifndef RENGINE_DEBUG
      #define RENGINE_DEBUG
      #endif
      printf("entered debug mode\n");
    }else if (memcmp(argv[1], help_string, strlen(help_string)) == 0) {
      printf("current launch options:\n");
      printf("\t--debug to enable debug mode\n");
      printf("\t--help to print this again!\n");
    }else{
      printf("use '--help' for launch parameters!\n");
    }
  }

  window_init(init, update, tick, render, shutdown, "assets/sprites/string_ball.png");
  window_updateloop();
  return 0;
};
