R"(
#version 330 core

in vec2 out_texturecoord;

uniform sampler2D texture;
uniform vec4 color;

out vec4 out_color;

void main() {
	out_color = texture(texture, out_texturecoord).rgba * vec4(color);
}
)"
