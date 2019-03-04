#include "meshdefaultmaterial.h"
#include "glmanager.h"

namespace se {

	MeshDefaultMaterial::MeshDefaultMaterial() {
		SetShader(GLManager::GetShader("Mesh Shader"));
	}

	void MeshDefaultMaterial::Init() {
		if (diffuse != nullptr) SetMainTexture(diffuse);
		if (normal != nullptr) SetTexture("normal", normal);
		if (bump != nullptr) SetTexture("bump", bump);
		if (specular != nullptr) SetTexture("specular", specular);
	}
}
