#include "baseshader.h"

namespace se {

	BaseShader::BaseShader() {
		/* LoadFromString(
			#include "base.vert"
			,
			#include "base.frag"
		); */

		name = "Base Shader";

		VertexShaderCode = R"glsl(
			#version 430

			layout(location=1) in vec3 vertex_coord;
			layout(location=5) uniform mat4 MVP;

			void main() {
				gl_Position = MVP * vec4(vertex_coord, 1.0);
			}
		)glsl";

		FragmentShaderCode = R"glsl(
			#version 430

			layout(location=6) uniform vec4 render_color;
			out vec4 frag_color;

			void main() {
				frag_color = render_color;
			}
		)glsl";
	}
}
