#include "shaders/wireframeshader.h"

namespace se {

	WireframeShader::WireframeShader() {

		name = "Wireframe Shader";

		VertexShaderCode = R"glsl(
			#version 430

			/*
				In questo shader il colore è deciso dall'array di vertex colors
			*/

			layout(location=1) in vec3 vertex_coord;
			layout(location=3) in vec4 vertex_color;
			uniform layout(location=5) mat4 MVP;

			uniform mat4 M;
			uniform vec2 viewport;
			uniform bool enabled_viewport;

			out vec4 rendered_color;

			void main() {

				if (enabled_viewport) {
					vec4 translated = M * vec4(vertex_coord.xy, 0.0f, 1.0f);
					gl_Position = vec4(2 * (translated.xy / viewport.xy) - 1, 0, 1);
				} else {
					gl_Position = MVP * vec4(vertex_coord, 1.0);
				}
				rendered_color = vertex_color;
			}

		)glsl";

		FragmentShaderCode = R"glsl(
			#version 430

			/*
				In questo shader il colore è deciso dall'array di vertex colors
			*/

			in vec4 rendered_color;
			out vec4 frag_color;

			void main() {
				frag_color = rendered_color;
			}

		)glsl";
	}

}
