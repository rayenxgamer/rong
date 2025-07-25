#include <graphics/camera.h>
#include <graphics/shader.h>
#include <graphics/texture.h>
#include <graphics/renderer.h>
#include <graphics/particlesystem/particle_emmiter.h>
#include <math/projection.h>
#include <math/common.h>
#include <math/aabb.h>
#include <math/vec2.h>
#include <game/ball.h>
#include <game/window.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define PLAYER_VERT_SPEED 8.0f
#define GRAVITY -1.0f

struct rect player1, player2, ball_rect;
struct rect background_rect;
struct shader debugshader;
struct shader textureshader;
struct ortho_camera cam;
struct ball ball_properties;
struct particle_list_node* head;
struct particle particle_default;
Texture loafer, string_ball, twach, background;
Texture star_particle;

vec2 player1_coords;
vec2 player2_coords;

unsigned int total_tick_count = 0;

void init(){
  player1_coords[0] = 590.0f; player1_coords[1] = 180.0f;
  player2_coords[0] = 25.0f; player2_coords[1] = 180.0f;

  srand(time(NULL));
  ball_properties.vel[0] = rand_range(-5, 5);
  ball_properties.vel[1] = rand_range(-5, 5);

  cam = camera_init_ortho((vec3){0.0f, 0.0f, 0.0f}, 0.0f, 640.0f, 0.0f, 480.0f, -1.0f, 1.0f);
  loafer = tex_create("../assets/sprites/player_loafer.png", true);
  string_ball = tex_create("../assets/sprites/string_ball.png", true);
  twach = tex_create("../assets/sprites/player_twach.png", true);
  star_particle = tex_create("../assets/sprites/star_purple_remastered_firstiteration.png", true);
  window_set_attributes(640, 480, "RONG: on the RENGINE!");

  particle_default.color = (color){0.5, .0, 0.5, 1.0};
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

  shader_create(&debugshader, "../shaders/vs.glsl", "../shaders/fs.glsl");
  shader_create(&textureshader, "../shaders/textureshaders/vs.glsl", "../shaders/textureshaders/fs.glsl");

  ball_rect = renderer_initrect_tex(320.0f, 240.0f, 25.0f, 25.0f, string_ball);
  player1 = renderer_initrect_tex(player1_coords[0], player1_coords[1], 120.0f, 25.0f, twach);
  player2 = renderer_initrect_tex(player2_coords[0], player2_coords[1], 120.0f, 25.0f, loafer);

  ball_properties.ball_rectangle = &ball_rect;
};

void render(){
  glClearColor(.0f, .0f, .0f, .0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glUseProgram(textureshader.handle);
  particles_update(head, &textureshader);

  renderer_drawrect_tex(player2, &textureshader);
  renderer_drawrect_tex(player1, &textureshader);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  renderer_drawrect_tex(ball_rect, &textureshader);
  glDisable(GL_BLEND);
};

void tick(){
  total_tick_count++;

  if(window_is_pressed(GLFW_KEY_ESCAPE))
    window_set_should_close();

  if (total_tick_count >= 2) {
    particles_emit(head, &textureshader);
    total_tick_count = 0;
  }
};

void update(float deltatime){
  glUseProgram(debugshader.handle);
  glUniformMatrix4fv(glGetUniformLocation(debugshader.handle, "projection"), 1, GL_FALSE, &cam.projection_matrix[0][0]);
  glUniformMatrix4fv(glGetUniformLocation(debugshader.handle, "view"), 1, GL_FALSE, &cam.view_matrix[0][0]);

  glUseProgram(textureshader.handle);
  glUniformMatrix4fv(glGetUniformLocation(textureshader.handle, "projection"), 1, GL_FALSE, &cam.projection_matrix[0][0]);
  glUniformMatrix4fv(glGetUniformLocation(textureshader.handle, "view"), 1, GL_FALSE, &cam.view_matrix[0][0]);
  rengine_math_ortho(cam.projection_matrix, cam.left, cam.right, cam.bottom, cam.top , cam.near, cam.far);

  if (window_is_pressed(GLFW_KEY_S))
    player1.y -= PLAYER_VERT_SPEED;

  if (window_is_pressed(GLFW_KEY_W))
    player1.y += PLAYER_VERT_SPEED;

  if (window_is_pressed(GLFW_KEY_K))
    player2.y -= PLAYER_VERT_SPEED;

  if (window_is_pressed(GLFW_KEY_I))
    player2.y += PLAYER_VERT_SPEED;

  //
  // ---------- debugging ----------
  if (window_is_pressed(GLFW_KEY_EQUAL))
    ball_properties.vel[0] += 1.0f;
  if (window_is_pressed(GLFW_KEY_MINUS))
    ball_properties.vel[1] -= 1.0f;
  // -------------------------------;
  //

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
};

void shutdown(){};

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
      printf("use '--help' for launch parameters!");
    }
  }

  window_init(init, update, tick, render, shutdown);
  window_updateloop();
  return 0;
};
