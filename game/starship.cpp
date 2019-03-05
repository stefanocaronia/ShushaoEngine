#include "starship.h"

using namespace se;

Starship::Starship() {

	using namespace glm;

	mr = AddComponent<MeshRenderer>();
	Mesh* cube = Resources::Get<Mesh>("cube");
	mr->SetMesh(Resources::Get<Mesh>("cube"));
	mr->material->SetMainTexture(Resources::Get<Texture>("cube_diffuse"));

	//transform->SetLocalPosition({0.0f, 0.0f, 20.0f});

}