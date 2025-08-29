#include "graphics/buffer.h"
#include "math/mat4.h"
#include <graphics/renderer.h>

void renderer_directdrawline(float xstart, float ystart, float xend, float yend, Shader shader){

  uint32_t vao = vao_create();
  uint32_t vbo = vbo_create();

  const float line_vertices_buffer[] = {
    xstart, ystart, xend, yend,
  };

  vao_bind(vao);
  vbo_bind(vbo);
  vbo_buffer(sizeof(line_vertices_buffer), line_vertices_buffer, GL_STATIC_DRAW);

  vao_attrib(vao, vbo, 0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

  glEnable(GL_LINE_SMOOTH);
  glHint(GL_LINE_SMOOTH_HINT,  GL_NICEST);

  glDrawArrays(GL_LINES, 0, 2);

  glDisable(GL_LINE_SMOOTH);
};

struct rect renderer_initrect_tex(float x, float y, float height, float width, Texture texture){
  uint32_t vao = vao_create();
  uint32_t vbo = vbo_create();
  uint32_t ibo = ibo_create();

  const float vertices_buffer[] = {
    0.0f,1.0f, 0.0f, 0.0f, 1.0f,
    1.0f,1.0f, 0.0f, 1.0f, 1.0f,
    1.0f,0.0f, 0.0f, 1.0f, 0.0f,

    0.0f,1.0f, 0.0f, 0.0f, 1.0f,
    1.0f,0.0f, 0.0f, 1.0f, 0.0f,
    0.0f,0.0f, 0.0f, 0.0f, 0.0f,
  };


  vao_bind(vao);
  vbo_bind(vbo);
  vbo_buffer(sizeof(vertices_buffer), vertices_buffer, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  struct rect self;
  self.x = x;
  self.y = y;
  self.height = height;
  self.width = width;
  self.texture = texture;
  self.vao_ = vao;
  return self;
};

void renderer_drawrect_tex(struct rect rectangle, Shader* shader){
  /* rendering code here */
  mat4 model1;
  mat4_identity(model1);

  mat4_translate(model1, (vec3){rectangle.x, rectangle.y, 0.0f});
  mat4_scalev_make(model1,(vec3){rectangle.width, rectangle.height, 0.0f});

  tex_bind(rectangle.texture);
  glUniform1i(glGetUniformLocation(shader->handle, "texture0"), 0);
  glUniformMatrix4fv(glGetUniformLocation(shader->handle, "model"), 1, GL_FALSE, &model1[0][0]);

  /* TODO: code to handle rotation */
  glActiveTexture(GL_TEXTURE0);
  tex_bind(rectangle.texture);
  glBindVertexArray(rectangle.vao_);
  glDrawArrays(GL_TRIANGLES, 0, 6);
};

struct rect renderer_initrect(float x, float y, float height, float width){
  uint32_t vao = vao_create();
  uint32_t vbo = vbo_create();
  uint32_t ibo = ibo_create();

  const float vertices_buffer[] = {
    0.0f,1.0f, 0.0f,
    1.0f,0.0f, 0.0f,
    0.0f,0.0f, 0.0f,

    0.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
  };

  vao_bind(vao);
  vbo_bind(vbo);
  vbo_buffer(sizeof(vertices_buffer), vertices_buffer, GL_STATIC_DRAW);

  vao_attrib(vao, vbo, 0, 3,  GL_FLOAT,  GL_FALSE,  3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  struct rect self = {x, y, height, width, vao, vbo};
  // more initialization code here
  return self;
};

void renderer_drawrect(struct rect rectangle, Shader* shader){
  /* rendering code here */
  glUseProgram(shader->handle);
  mat4 model;
  mat4_identity(model);

  mat4_translate(model, (vec3){rectangle.x, rectangle.y, 0.0f});
  mat4_scalev_make(model,(vec3){rectangle.height, rectangle.width, 0.0f});

  shader_setm4x4(*shader, "model", model);

  /* TODO: code to handle rotation */
  vao_bind(rectangle.vao_);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  return;
};

struct rect renderer_init_particles(struct rect* rectangle, Color color, Shader* shader){
  glGenVertexArrays(1, &rectangle->vao_);
  uint32_t vbo = vbo_create();
  uint32_t ibo = ibo_create();

  const float vertices_buffer[] = {
    0.0f,1.0f, 0.0f,
    1.0f,0.0f, 0.0f,
    0.0f,0.0f, 0.0f,

    0.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
  };

  glBindVertexArray(rectangle->vao_);
  vbo_bind(rectangle->vao_);
  vbo_buffer(sizeof(vertices_buffer), vertices_buffer, GL_STATIC_DRAW);

  vao_attrib(rectangle->vao_, vbo, 0, 3,  GL_FLOAT,  GL_FALSE,  3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  return *rectangle;
}

void renderer_drawrect_particle(struct rect* rectangle, Color color, Shader* shader){
  /* rendering code here */
  mat4 model1;
  mat4_identity(model1);

  mat4_translate(model1, (vec3){rectangle->x, rectangle->y, 0.0f});
  mat4_scalev_make(model1,(vec3){rectangle->width, rectangle->height, 0.0f});

  tex_bind(rectangle->texture);
  glUniform1i(glGetUniformLocation(shader->handle, "texture0"), 0);
  glUniformMatrix4fv(glGetUniformLocation(shader->handle, "model"), 1, GL_FALSE, &model1[0][0]);
  glUniform1f(glGetUniformLocation(shader->handle, "color"), color.a);

  /* TODO: code to handle rotation */
  glActiveTexture(GL_TEXTURE0);
  tex_bind(rectangle->texture);
  glBindVertexArray(rectangle->vao_);

  glDrawArrays(GL_TRIANGLES, 0, 6);
};

background_props renderer_initbackground(background_props props){
  uint32_t vao = vao_create();
   uint32_t vbo = vbo_create();

  const float vertices_buffer[] = {
    0.0f,1.0f, 0.0f, 0.0f, 1.0f,
    1.0f,1.0f, 0.0f, 1.0f, 1.0f,
    1.0f,0.0f, 0.0f, 1.0f, 0.0f,

    0.0f,1.0f, 0.0f, 0.0f, 1.0f,
    1.0f,0.0f, 0.0f, 1.0f, 0.0f,
    0.0f,0.0f, 0.0f, 0.0f, 0.0f,
  };

  vao_bind(vao);
  vbo_bind(vbo);
  vbo_buffer(sizeof(vertices_buffer), vertices_buffer, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  return (background_props){props.window_height, props.window_width, props.texture2D, vao};
}

void renderer_drawbackground(background_props* props ,Shader* shader){
  mat4 model;
  mat4_identity(model);

  mat4_translate(model, (vec3){0, 0, 0.0f});
  mat4_scalev_make(model,(vec3){props->window_width, props->window_height, 0.0f});

  tex_bind(props->texture2D);
  glUniform1i(glGetUniformLocation(shader->handle, "texture0"), 0);
  glUniformMatrix4fv(glGetUniformLocation(shader->handle, "model"), 1, GL_FALSE, &model[0][0]);

  glActiveTexture(GL_TEXTURE0);
  tex_bind(props->texture2D);

  glBindVertexArray(props->vao);
  glDrawArrays(GL_TRIANGLES, 0, 6);
}


struct rect renderer_initatlas(Atlas atlas, vec4 position, float x, float y, float height, float width){
  vec4 pos;
  vec4_copy(pos, position);

  uint32_t vao = vao_create();
  uint32_t vbo = vbo_create();

  const float vertices_buffer[] = {
    // TODO: make this look better
    0.0f,1.0f, 0.0f, position[0], position[1], // top left
    1.0f,1.0f, 0.0f, position[2], position[1], // top right
    1.0f,0.0f, 0.0f, position[2], position[3], // bottom right

    0.0f,1.0f, 0.0f, position[0], position[1], // top left
    0.0f,0.0f, 0.0f, position[0], position[3], // bottom left
    1.0f,0.0f, 0.0f, position[2], position[3], // bottom right
  };

  vao_bind(vao);
  vbo_bind(vbo);
  vbo_buffer(sizeof(vertices_buffer), vertices_buffer, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  return (struct rect){
    .x = x, .y = y,
    .width = width,
    .height = height,
    .vao_ = vao,
  };
}

void renderer_drawfromatlas(Atlas atlas, struct rect* rectangle , Shader* shader){
  vao_bind(rectangle->vao_);
  mat4 model;

  mat4_identity(model);

  mat4_translate(model, (vec3){rectangle->x, rectangle->y, 0.0f});
  mat4_scalev_make(model,(vec3){rectangle->width, rectangle->height, 0.0f});

  tex_bind(*atlas.texture);
  glUniform1i(glGetUniformLocation(shader->handle, "texture0"), 0);
  glUniformMatrix4fv(glGetUniformLocation(shader->handle, "model"), 1, GL_FALSE, &model[0][0]);

  glActiveTexture(GL_TEXTURE0);

  glBindVertexArray(rectangle->vao_);
  glDrawArrays(GL_TRIANGLES, 0, 6);
}
