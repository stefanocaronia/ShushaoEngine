#include "baseshader.h"

namespace se {

	BaseShader::BaseShader() {
		LoadFromString(
			#include "base.vert"
			,
			#include "base.frag"
		);

		name = "Base Shader";
	}
}
