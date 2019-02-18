R"(
#version 330 core

in vec2 out_texturecoord;

uniform sampler2D uTexture;
uniform vec4 uColor;

out vec4 out_color;

void main(void) {
	out_color = vec4(1, 1, 1, texture2D(uTexture, out_texturecoord).a) * uColor;
}

)"
