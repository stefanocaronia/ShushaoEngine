#include "starship.h"

using namespace se;

Starship::Starship() {

	using namespace glm;

	MeshRenderer* mr = AddComponent<MeshRenderer>();

	mr->mesh = Resources::Get<Mesh>("cube");
	mr->material->SetMainTexture(Resources::Get<Texture>("cube"));

	//transform->SetLocalPosition({0.0f, 0.0f, 20.0f});

}