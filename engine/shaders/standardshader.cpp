#include "shaders/standardshader.h"
#include "../resources.h"

namespace se {

	StandardShader::StandardShader() {
		name = "Standard Shader";

		VertexShaderCode = Resources::GetEmbeddedText(STANDARDSHADER_VERT);
		FragmentShaderCode = Resources::GetEmbeddedText(STANDARDSHADER_FRAG);
	}

	void StandardShader::Awake() {

		// custom uniforms
		AddUniform("Diffuse Map", "diffuse_map", UniformType::TEXTURE);
		AddUniform("Render Color", "render_color", UniformType::TEXTURE, ShaderLocation::LOCATION_RENDER_COLOR);

		// valorizzazione
		SetTextureIndex("diffuse_map", 0);
	}
}
