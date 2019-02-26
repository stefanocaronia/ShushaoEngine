R"(
#version 430

/*
	In questo shader il colore è deciso dall'array di vertex colors
*/

layout(location=1) in vec3 vertex_coord;
layout(location=3) in vec4 vertex_color;
uniform layout(location=5) mat4 MVP;

out vec4 rendered_color;

void main() {
	gl_Position = MVP * vec4(vertex_coord, 1.0);
	rendered_color = vertex_color;
}

)"
