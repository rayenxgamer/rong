#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture0;

void main(){
   FragColor = texture(texture0, TexCoords);
  // FragColor = vec4(1.0f,1.0f,1.0f,1.0f);
};
