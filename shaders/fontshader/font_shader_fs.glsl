#version 330 core

#define WHITE vec3(1.0, 1.0, 1.0)

out vec4 FragColor;

in vec2 TexCoords;

uniform vec4 color;
uniform sampler2D texture0;

void main(){
  // vec4 texture_data = texture(texture0, TexCoords);
  // fragcolor = vec4(texture_data.rgb, texture_data.a * color);

  vec4 texture_data = texture(texture0, TexCoords);

  if (texture_data.rgb == vec3(1.0, 1.0 , 1.0)){
    FragColor = vec4(color);
  } else {
    FragColor = vec4(texture_data);
  }
};
