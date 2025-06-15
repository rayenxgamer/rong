#include <graphics/buffer.h>

uint32_t vao_create(){
  uint32_t vao;
  glGenVertexArrays(1, &vao);
  if(vao == GL_INVALID_VALUE){
    printf("invalid vao generated!\n");
    return 0;
  }
  return vao;
};

void vao_bind(uint32_t vao){
  glBindVertexArray(vao);
};

void vao_attrib(uint32_t vao, uint32_t vbo, GLuint index, GLint size
,GLenum type, GLboolean normalized, GLsizei stride,void* offset){

  if (vao < 0)
    printf("invalid vao!\n");
  vao_bind(vao);
  if (vbo < 0)
    printf("invalid vbo!\n");

  switch (type) {
    case GL_FLOAT:
      glVertexAttribPointer(index, size, type, normalized, stride, offset);
      printf("you chose glFLoat! congrats! you're basic asf\n");
    case GL_INT:
      glVertexAttribIPointer(index, size, normalized, stride, (GLvoid*)offset);
    case GL_BYTE:
    case GL_UNSIGNED_BYTE:
    case GL_SHORT:
    case GL_UNSIGNED_SHORT:
    case GL_UNSIGNED_INT:
    case GL_HALF_FLOAT:
    case GL_DOUBLE:
    case GL_INT_2_10_10_10_REV:
      glVertexAttribIPointer(index, size, normalized, stride, (GLvoid*)offset);
    case GL_UNSIGNED_INT_2_10_10_10_REV:
    default:
      printf("enter a proper type for the vao!\n");
  }
  glEnableVertexAttribArray(index);
};

uint32_t vbo_create(){
  uint32_t vbo;
  glGenBuffers(1, &vbo);
  if (vbo == GL_INVALID_VALUE){
    printf("invalid vbo generated!\n");
    return 0;
  }
  return vbo;
};

void vbo_bind(uint32_t vbo){
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  if (vbo == GL_INVALID_VALUE){
    printf("you're binding a vertex buffer that wasnt previously made! make sure to bind a proper buffer\n");
    return;
  }
};

void vbo_buffer(size_t size, const void* data, GLenum usage){
  glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}

uint32_t ibo_create(){
  uint32_t ibo;
  glGenBuffers(1, &ibo);
  if (ibo == GL_INVALID_VALUE){
    printf("invalid vbo generated!\n");
    return 0;
  }
  return ibo;
}

void ibo_bind(uint32_t ibo){
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
  if (ibo == GL_INVALID_VALUE){
    printf("you're binding a vertex buffer that wasnt previously made! make sure to bind a proper buffer\n");
    return;
  }
};

void ibo_buffer(size_t size, const void *data, GLenum usage){
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
}
