#include "spritesdefaultmaterial.h"
#include "standardshader.h"

namespace se {

	SpritesDefaultMaterial::SpritesDefaultMaterial() {
		SetShader(new StandardShader());
	}
}
