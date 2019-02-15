#version 330 core

layout(location=0) in vec3 position;
layout(location=2) in vec4 color;
uniform mat4 MVP;

out vec4 renderer_color;

void main() {
	gl_Position = MVP * vec4(position, 1.0);
	renderer_color = color;
}
