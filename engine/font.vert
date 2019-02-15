R"(
#version 330 core

in vec4 position;

uniform mat4 mvp;
out vec2 out_texturecoord;

void main(void) {
	gl_Position = mvp * vec4(position.xy, 0.0f, 1.0f);
	out_texturecoord = position.zw;
}

)"
