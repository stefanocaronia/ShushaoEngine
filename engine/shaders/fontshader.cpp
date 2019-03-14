#include "shaders/fontshader.h"

namespace se {

	FontShader::FontShader() {

		name = "Font Shader";

		VertexShaderCode = R"glsl(
			#version 430

			layout(location=1) in vec4 vertex_coord;
			layout(location=5) uniform mat4 MVP;

			uniform mat4 M;

			uniform vec2 viewport;
			uniform bool enabled_viewport;

			out vec2 UV;

			void main(void) {

				if (enabled_viewport) {
					vec4 translated = M * vec4(vertex_coord.xy, 0.0f, 1.0f);
					gl_Position = vec4(2 * (translated.xy / viewport.xy) - 1, 0, 1);
				} else {
					gl_Position = MVP * vec4(vertex_coord.xy, 0.0f, 1.0f);
				}

				UV = vertex_coord.zw;
			}

		)glsl";

		FragmentShaderCode = R"glsl(
			#version 430

			in vec2 UV;

			layout(location=6) uniform vec4 render_color;

			uniform sampler2D diffuse_map;
			uniform bool enabled_viewport;

			out vec4 frag_color;

			void main(void) {
				frag_color = vec4(1, 1, 1, texture2D(diffuse_map, UV).r) * render_color;
			}

		)glsl";
	}

	void FontShader::Awake() {

		AddUniform("Diffuse Map", "diffuse_map", UniformType::TEXTURE);

		AddShaderUniform("M", UniformType::MATRIX);
		AddShaderUniform("viewport", UniformType::VECTOR);
		AddShaderUniform("enabled_viewport", UniformType::INTEGER);

		SetTextureIndex("diffuse_map", 0);
	}
}
