#version 330 core

in vec2 TexCoords;
out vec4 FragColor;

uniform float color;
uniform sampler2D texture0;

void main(){
  vec4 texture_data = texture(texture0, TexCoords);
  FragColor = vec4(texture_data.rgb, texture_data.a * color);
}
