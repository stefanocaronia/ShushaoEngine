#include "starship.h"

using namespace se;

Starship::Starship() {

	using namespace glm;

	MeshRenderer* mr = AddComponent<MeshRenderer>();

	mr->material->SetMainTexture(Resources::Get<Texture>("ufo_diffuse"));

}