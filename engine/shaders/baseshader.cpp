#include "shaders/baseshader.h"
#include "../resources.h"

namespace se {

	BaseShader::BaseShader() {
		VertexShaderCode = Resources::GetEmbeddedText(BASESHADER_VERT);
		FragmentShaderCode = Resources::GetEmbeddedText(BASESHADER_FRAG);
	}

	void BaseShader::Awake() {
		AddShaderUniform("M", UniformType::MATRIX);
		AddShaderUniform("viewport", UniformType::VECTOR);
		AddShaderUniform("enabled_viewport", UniformType::INTEGER);
	}
}
