#include "spritesdefaultmaterial.h"
#include "standardshader.h"
#include "glmanager.h"

namespace se {

	SpritesDefaultMaterial::SpritesDefaultMaterial() {
		// SetShader(new StandardShader());
		SetShader(GLManager::GetShader("Standard Shader"));
	}
}
