#version 330 core

in vec2 out_texturecoord;

uniform sampler2D base_texture;
uniform vec4 renderer_color;

out vec4 out_color;

void main() {
	out_color = texture(base_texture, out_texturecoord).rgba * vec4(renderer_color);
}
