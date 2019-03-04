#include "fontshader.h"

namespace se {

	FontShader::FontShader() {

		name = "Font Shader";

		VertexShaderCode = R"glsl(
			#version 430

			layout(location=8) in vec4 vertex_coord;

			layout(location=5) uniform mat4 MVP;
			out vec2 out_texturecoord;

			void main(void) {
				gl_Position = MVP * vec4(vertex_coord.xy, 0.0f, 1.0f);
				out_texturecoord = vertex_coord.zw;
			}

		)glsl";

		FragmentShaderCode = R"glsl(
			#version 430

			in vec2 out_texturecoord;

			layout(location=6) uniform vec4 render_color;
			layout(location=7) uniform sampler2D main_texture;

			out vec4 frag_color;

			void main(void) {
				frag_color = vec4(1, 1, 1, texture2D(main_texture, out_texturecoord).r) * render_color;
			}

		)glsl";
	}

	void FontShader::Awake() {
		SetTexture("main_texture", GL_TEXTURE0);
	}
}
