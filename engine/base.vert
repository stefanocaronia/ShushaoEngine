R"(
#version 330 core

layout(location=0) in vec3 aCoord;
uniform mat4 uMvp;

void main() {
	gl_Position = uMvp * vec4(aCoord, 1.0);
}
)"
