R"(
#version 330 core

in vec2 out_texturecoord;

uniform sampler2D textureid;
uniform vec4 color;

out vec4 out_color;

void main() {
	out_color = texture(textureid, out_texturecoord).rgba * vec4(color);
}
)"
