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

		AddShaderUniform("image_border", UniformType::VECTOR);
		AddShaderUniform("sprite_border", UniformType::VECTOR);
		AddShaderUniform("image_size", UniformType::VECTOR);
		AddShaderUniform("texture_size", UniformType::VECTOR);
		AddShaderUniform("enabled_sliced", UniformType::INTEGER);
		AddShaderUniform("enabled_tiled", UniformType::INTEGER);
		AddShaderUniform("sliced_fill", UniformType::INTEGER);

		// valorizzazione
		SetTextureIndex("diffuse_map", 0);
	}
}
