#include "fontshader.h"

namespace se {

	FontShader::FontShader() {
		LoadFromString(
			#include "font.vert"
			,
			#include "font.frag"
		);

		name = "Font Shader";
	}

	void FontShader::Awake() {
		SetTexture("main_texture", GL_TEXTURE0);
	}
}
