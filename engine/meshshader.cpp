#include "meshshader.h"

namespace se {

	MeshShader::MeshShader() {
		name = "Mesh Shader";

		VertexShaderCode = R"glsl(
			#version 430
			/*	Standard Mesh Shader */

			layout(location=1) in vec3 vertex_coord;
			layout(location=2) in vec2 texture_coord;

			layout(location=5) uniform mat4 MVP;

			out vec2 UV;

			void main() {
				gl_Position = MVP * vec4(vertex_coord, 1.0);
				UV = texture_coord;
			}

		)glsl";

		FragmentShaderCode = R"glsl(
			#version 430
			/*	Standard Mesh Shader */

			in vec2 UV;

			layout(location=6) uniform vec4 render_color;
			layout(location=7) uniform sampler2D diffuse_map;

			uniform sampler2D normal_map;
			uniform sampler2D bump_map;
			uniform sampler2D specular_map;

			uniform vec4 ambient_color;
			uniform vec4 diffuse_color;
			uniform vec4 specular_color;

			out vec3 frag_color;

			void main() {
				frag_color = texture(diffuse_map, UV).rgb;
			}

		)glsl";
	}

	void MeshShader::Awake() {

		// custom uniforms
		AddUniform("Ambient reflection", "ambient_color", UniformType::COLOR);
		AddUniform("Diffuse reflection", "diffuse_color", UniformType::COLOR);
		AddUniform("Specular reflection", "specular_color", UniformType::COLOR);

		AddUniform("Normal Map", "normal_map", UniformType::TEXTURE);
		AddUniform("Bump Map", "bump_map", UniformType::TEXTURE);
		AddUniform("Specular Map", "specular_map", UniformType::TEXTURE);

		// valorizzazione
		SetTexture("diffuse_map", GL_TEXTURE0);
		SetTexture("normal_map", GL_TEXTURE1);
		SetTexture("bump_map", GL_TEXTURE2);
		SetTexture("specular_map", GL_TEXTURE3);
	}
}
