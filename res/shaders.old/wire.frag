#version 330 core

in vec4 renderer_color;

out vec4 out_color;

void main() {
	out_color = vec4(renderer_color);
}
