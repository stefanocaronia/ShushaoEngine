R"(
#version 430

in vec2 out_texturecoord;

layout(location=6) uniform vec4 render_color;
layout(location=7) uniform sampler2D main_texture;

out vec4 frag_color;

void main(void) {
	frag_color = vec4(1, 1, 1, texture2D(main_texture, out_texturecoord).a) * render_color;
}

)"
