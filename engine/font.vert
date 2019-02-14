R"(
#version 330 core

layout(location=0) in vec4 position;

uniform mat4 MVP;
out vec2 out_texturecoord;

void main(void) {
	gl_Position = MVP * vec4(position.xy, 0.0f, 1.0f);
	out_texturecoord = position.zw;
}

)"
