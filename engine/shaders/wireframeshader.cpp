#include "wireframeshader.h"
#include "../resources.h"

namespace se {

	WireframeShader::WireframeShader() {

		name = "Wireframe Shader";

		VertexShaderCode = Resources::GetEmbeddedText(WIREFRAMESHADER_VERT);
		FragmentShaderCode = Resources::GetEmbeddedText(WIREFRAMESHADER_FRAG);
	}

}
