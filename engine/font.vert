R"(
#version 330 core

in vec4 aCoord;

uniform mat4 uMvp;
out vec2 out_texturecoord;

void main(void) {
	gl_Position = uMvp * vec4(aCoord.xy, 0.0f, 1.0f);
	out_texturecoord = aCoord.zw;
}

)"
