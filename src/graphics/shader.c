#include <graphics/shader.h>

static uint32_t shader_checkerrors(uint32_t handle){
  uint32_t success;

  glGetShaderiv(handle, GL_COMPILE_STATUS, (int*)&success);

  if (!success) {
    char logbuffer[512];
    glGetShaderInfoLog(handle, sizeof(logbuffer), NULL, logbuffer);
    printf("failed to compile shader: %s\n", logbuffer);
  }

  return success;
};

static uint32_t shader_compile(const char *shaderpath, GLenum type){
  char* text;
  long size;

  FILE* filep;
  filep = fopen(shaderpath, "r");

  if (filep == NULL) {
    printf("could not open shader file\n");
    exit(1);
  }

  fseek(filep, 0, SEEK_END);
  size = ftell(filep);
  assert(size > 0);
  fseek(filep, 0, SEEK_SET);
  text = malloc(size * sizeof(long));
  memset(text, 0, size * sizeof(long));
  assert(text != NULL);
  fread(text, 1, size, filep);

  fclose(filep);

  uint32_t temp_shader_handle;
  temp_shader_handle = glCreateShader(type);
  glShaderSource(temp_shader_handle, 1, (const GLchar *const*)&text, NULL);
  glCompileShader(temp_shader_handle);

  assert(shader_checkerrors(temp_shader_handle) > 0);

  free(text);

  return temp_shader_handle;
}

struct shader shader_create(const char *vpath, const char *fpath){
  struct shader self;

  uint32_t success_program;

  self.vs_handle = shader_compile(vpath, GL_VERTEX_SHADER);
  self.fs_handle = shader_compile(fpath, GL_FRAGMENT_SHADER);
  self.handle = glCreateProgram();

  glAttachShader(self.handle, self.vs_handle);
  glAttachShader(self.handle, self.fs_handle);
  glLinkProgram(self.handle);

  glGetProgramiv(self.handle, GL_LINK_STATUS, (int*)&success_program);
  if (!success_program) {
    char info_program_log[512];
    glGetProgramInfoLog(self.handle, sizeof(info_program_log), NULL, info_program_log);
  }

  glDeleteShader(self.vs_handle);
  glDeleteShader(self.fs_handle);

  return self;
};

void shader_bind(struct shader self){
  glUseProgram(self.handle);
};

void shader_setb(struct shader shader, const char* name, bool value){
  glUniform1i(glGetUniformLocation(shader.handle, name), value);
};

void shader_seti(struct shader shader, const char* name, int value){
  glUniform1i(glGetUniformLocation(shader.handle, name), value);
};

void shader_setui(struct shader shader, const char* name, uint32_t value){
  glUniform1ui(glGetUniformLocation(shader.handle, name), value);
};

void shader_setf(struct shader shader, const char* name, float value){
  glUniform1f(glGetUniformLocation(shader.handle, name), value);
};

void shader_setv4(struct shader shader, const char* name, vec4 value){
  glUniform4fv(glGetUniformLocation(shader.handle, name),1, &value[0]);
};

void shader_setv3(struct shader shader, const char* name, vec3 value){
  glUniform3fv(glGetUniformLocation(shader.handle, name),1, &value[0]);
};
