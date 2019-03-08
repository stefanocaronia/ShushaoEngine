#include "fontshader.h"

namespace se {

	FontShader::FontShader() {

		name = "Font Shader";

		VertexShaderCode = R"glsl(
			#version 430

			layout(location=11) in vec4 vertex_coord;

			layout(location=5) uniform mat4 MVP;
			out vec2 UV;

			void main(void) {
				gl_Position = MVP * vec4(vertex_coord.xy, 0.0f, 1.0f);
				UV = vertex_coord.zw;
			}

		)glsl";

		FragmentShaderCode = R"glsl(
			#version 430

			in vec2 UV;

			layout(location=6) uniform vec4 render_color;
			layout(location=7) uniform sampler2D diffuse_map;

			out vec4 frag_color;

			void main(void) {
				frag_color = vec4(1, 1, 1, texture2D(diffuse_map, UV).r) * render_color;
			}

		)glsl";
	}

	void FontShader::Awake() {

		AddUniform("Diffuse Map", "diffuse_map", UniformType::TEXTURE, ShaderLocation::LOCATION_DIFFUSE_MAP);

		SetTexture("diffuse_map", GL_TEXTURE0);
	}
}
