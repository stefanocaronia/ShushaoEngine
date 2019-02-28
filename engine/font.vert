R"(
#version 430

layout(location=1) in vec4 vertex_coord;

layout(location=5) uniform mat4 MVP;
out vec2 out_texturecoord;

void main(void) {
	gl_Position = MVP * vec4(vertex_coord.xy, 0.0f, 1.0f);
	out_texturecoord = vertex_coord.zw;
}

)"
