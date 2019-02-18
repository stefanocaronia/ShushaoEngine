R"(

#version 330 core

layout(location=0) in vec3 aCoord;
layout(location=2) in vec4 aColor;
uniform mat4 uMvp;

out vec4 rendered_color;

void main() {
	gl_Position = uMvp * vec4(aCoord, 1.0);
	rendered_color = aColor;
}

)"
