R"(
#version 330 core

in vec2 out_texturecoord;

uniform sampler2D uTextureId;
uniform vec4 uColor;

out vec4 out_color;

void main() {
	out_color = texture(uTextureId, out_texturecoord).rgba * vec4(uColor);
}
)"
