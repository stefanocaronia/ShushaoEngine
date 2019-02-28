#include "wireframeshader.h"

namespace se {

	WireframeShader::WireframeShader() {
		LoadFromString(
			#include "wire.vert"
			,
			#include "wire.frag"
		);

		name = "Wireframe Shader";
	}

}
