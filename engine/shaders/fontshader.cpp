#include "shaders/fontshader.h"
#include "../resources.h"

namespace se {

	FontShader::FontShader() {
		name = "Font Shader";

		VertexShaderCode = Resources::GetEmbeddedText(FONTSHADER_VERT);
		FragmentShaderCode = Resources::GetEmbeddedText(FONTSHADER_FRAG);

	}

	void FontShader::Awake() {

		AddUniform("Diffuse Map", "diffuse_map", UniformType::TEXTURE);

		AddShaderUniform("M", UniformType::MATRIX);
		AddShaderUniform("viewport", UniformType::VECTOR);
		AddShaderUniform("enabled_viewport", UniformType::INTEGER);

		SetTextureIndex("diffuse_map", 0);
	}
}
