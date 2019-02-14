R"(
#version 330 core

layout(location=0) in vec4 position;
layout(location=1) in vec2 texturecoord;

uniform mat4 MVP;
out vec2 out_texturecoord;

void main(void) {
  gl_Position = MVP * vec4(position.xy, 1.0);
  out_texturecoord = position.zw;
}

)"
