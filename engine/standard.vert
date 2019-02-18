R"(
#version 330 core

layout(location=0) in vec3 aCoord;
layout(location=1) in vec2 aTextureCoord;

uniform mat4 uMvp;
out vec2 out_texturecoord;

void main() {
	gl_Position = uMvp * vec4(aCoord, 1.0);
	out_texturecoord = aTextureCoord;
}
)"
