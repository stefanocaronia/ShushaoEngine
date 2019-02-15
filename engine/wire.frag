R"(

#version 330 core

in vec4 rendered_color;

out vec4 out_color;

void main() {
	out_color = vec4(rendered_color);
}

)"
