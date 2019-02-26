#include "standardshader.h"

namespace se {

	StandardShader::StandardShader() {
		LoadFromString(
			#include "standard.vert"
			,
			#include "standard.frag"
		);

		name = "Standard Shader";
	}

	void StandardShader::Awake() {

		// custom uniforms
		// AddUniform("Main Texture Offset", "main_texture_offset", UniformType::VECTOR);

		// valorizzazione
		SetTexture("main_texture", GL_TEXTURE0);
	}

	void StandardShader::Update() {
	}

}
