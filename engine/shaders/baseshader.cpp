#include "shaders/baseshader.h"
#include "../resources.h"

namespace se {

	BaseShader::BaseShader() {
		VertexShaderCode = Resources::GetEmbeddedText(BASESHADER_VERT);
		FragmentShaderCode = Resources::GetEmbeddedText(BASESHADER_FRAG);
	}

	void BaseShader::Awake() {
		AddShaderUniform("M", Uniform::Type::MATRIX);
		AddShaderUniform("viewport", Uniform::Type::VECTOR);
		AddShaderUniform("enabled_viewport", Uniform::Type::INTEGER);
	}
}
