R"(
#version 430

layout(location=1) in vec3 vertex_coord;
layout(location=5) uniform mat4 MVP;

void main() {
	gl_Position = MVP * vec4(vertex_coord, 1.0);
}
)"
