#include "starship.h"

using namespace se;

Starship::Starship() {

	using namespace glm;

	mr = AddComponent<MeshRenderer>();
	mr->SetMesh(Resources::Get<Mesh>("cube"));
	mr->material->SetMainTexture(Resources::Get<Texture>("tap"));

	// transform->SetLocalScale({2.0f, 2.0f, 2.0f});

}