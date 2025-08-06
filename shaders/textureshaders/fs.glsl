#version 330 core

out vec4 FragColor;

in vec2 TexCoords;
uniform float color;

uniform sampler2D texture0;

void main(){
  FragColor = texture(texture0, TexCoords);
  // FragColor = vec4(texture_data.rgb, color);
  // FragColor = vec4(1.0f,1.0f,1.0f,1.0f);
};
