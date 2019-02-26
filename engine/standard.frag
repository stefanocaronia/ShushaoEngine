R"(
#version 430

in vec2 out_texturecoord;

layout(location=6) uniform vec4 render_color;
layout(location=7) uniform sampler2D main_texture;

out vec4 frag_color;

void main() {

	//vec4 color = texture2D(main_texture, out_texturecoord);
	//if (color.w < 1) frag_color = vec4(1,0,0,0); else frag_color = vec4(0,1,0,1);
	frag_color = texture2D(main_texture, out_texturecoord) * vec4(render_color);

	// if (frag_color.a < 0.1) discard;
}
)"
