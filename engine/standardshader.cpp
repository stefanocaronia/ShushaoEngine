#include "standardshader.h"

namespace se {

	StandardShader::StandardShader() {
		name = "Standard Shader";

		VertexShaderCode = R"glsl(
			#version 430
			/*	Standard Vertex Shader */

			layout(location=1) in vec3 vertex_coord;
			layout(location=2) in vec2 texture_coord;

			layout(location=5) uniform mat4 MVP;

			out vec2 out_texturecoord;

			void main() {
				gl_Position = MVP * vec4(vertex_coord, 1.0);
				out_texturecoord = texture_coord;
			}
		)glsl";

		FragmentShaderCode = R"glsl(
			#version 430
			/*	Standard Fragment Shader */

			in vec2 out_texturecoord;

			layout(location=6) uniform vec4 render_color;
			layout(location=7) uniform sampler2D diffuse_map;

			out vec4 frag_color;

			void main() {
				frag_color = texture2D(diffuse_map, out_texturecoord) * vec4(render_color);
			}
		)glsl";
	}

	void StandardShader::Awake() {

		// custom uniforms
		// AddUniform("Main Texture Offset", "diffuse_map_offset", UniformType::VECTOR);

		// valorizzazione
		SetTexture("diffuse_map", GL_TEXTURE0);
	}

}
