#include "glad/gl.h"
#include <graphics/texture.h>
#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture tex_create(const char* path, bool flipped){
  uint32_t textureHandle;

  glGenTextures(1, &textureHandle);

  if (!textureHandle){
    printf("failed to generate texture with path%s\n", path);
  }

  glBindTexture(GL_TEXTURE_2D, textureHandle);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  if (flipped) {
    stbi_set_flip_vertically_on_load(true);
  }

  int width, height, channels;
  unsigned char* data = stbi_load(path, &width, &height, &channels, 0);

  if (!data) {
    printf("couldn't load image using stb at%s\n", path);
    exit(1);
  }

  switch (channels){
    case 1:
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, data);
      break;
    case 3:
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
      break;
    case 4:
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
      break;
    default:
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
  }

  glGenerateMipmap(GL_TEXTURE_2D);
  stbi_image_free(data);

  Texture self = {textureHandle, path, flipped, height, width};
  return self;
}

void tex_bind(Texture texture){
  glBindTexture(GL_TEXTURE_2D, texture.handle);
};
