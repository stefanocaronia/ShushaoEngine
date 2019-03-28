#include "shaders/particlesshader.h"
#include "../resources.h"

namespace se {

	ParticlesShader::ParticlesShader() {
		name = "Particles Shader";

		VertexShaderCode = Resources::GetEmbeddedText(PARTICLESSHADER_VERT);
		FragmentShaderCode = Resources::GetEmbeddedText(PARTICLESSHADER_FRAG);
		GeometryShaderCode = Resources::GetEmbeddedText(PARTICLESSHADER_GEOM);
	}

	void ParticlesShader::Awake() {

		// custom uniforms
		AddUniform("Diffuse Map", "diffuse_map", UniformType::TEXTURE);
		AddUniform("Render Color", "render_color", UniformType::TEXTURE, ShaderLocation::LOCATION_RENDER_COLOR);

		// shader controlled uniforms (locked)
		AddShaderUniform("P", UniformType::MATRIX);

		// valorizzazione
		SetTextureIndex("diffuse_map", 0);
	}
}
