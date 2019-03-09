#include "starship.h"

using namespace se;

Starship::Starship() {

	using namespace glm;

	mr = AddComponent<MeshRenderer>();
	mr->SetMesh(Resources::Get<Mesh>("cube"));

	mr->material->SetTexture("diffuse_map", Resources::Get<Texture>("cube_diffuse"));
	mr->material->SetTexture("specular_map", Resources::Get<Texture>("cube_specular"));
	// mr->material->SetColor("ambient_color", {0.0215f, 	0.1745f, 	0.0215f});
	// mr->material->SetColor("diffuse_color", {0.07568f, 	0.61424f, 	0.07568f});
	// mr->material->SetColor("specular_color", {0.633f, 	0.727811f, 	0.633f});
	mr->material->SetFloat("shininess", 24.0f);

	//transform->SetLocalScale({1.0f, 1.0f, 1.0f});

}

