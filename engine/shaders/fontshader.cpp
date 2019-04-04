#include "fontshader.h"
#include "../resources.h"

namespace se {

	FontShader::FontShader() {
		name = "Font Shader";

		VertexShaderCode = Resources::GetEmbeddedText(FONTSHADER_VERT);
		FragmentShaderCode = Resources::GetEmbeddedText(FONTSHADER_FRAG);

	}

	void FontShader::Awake() {

		AddUniform("Diffuse Map", "diffuse_map", Uniform::Type::TEXTURE);

		AddShaderUniform("M", Uniform::Type::MATRIX);
		AddShaderUniform("viewport", Uniform::Type::VECTOR);
		AddShaderUniform("enabled_viewport", Uniform::Type::INTEGER);

		SetTextureIndex("diffuse_map", 0);
	}
}
