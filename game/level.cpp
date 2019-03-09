#include "globals.h"
#include "level.h"
#include "pancrazio.h"
#include "starship.h"
#include "mover.h"

Level::Level() {

	using namespace se;

	Entity* directional = AddEntity("Directional");
	directional->transform->SetLocalRotation({20,10,0});
	Light* light = directional->AddComponent<Light>();
	light->type = LightType::DIRECTIONAL;
	light->ambient  = {0.1f, 0.1f, 0.1f};
	light->diffuse  = {0.8f, 0.8f, 0.8f};
	light->specular = {1.0f, 1.0f, 1.0f};

	Entity* point = AddEntity("Point 1");
	point->transform->SetLocalPosition({3.0f, 0.0f, 4.0f});
	Light* plight =point->AddComponent<Light>();
	plight->type = LightType::POINT;
	plight->ambient  = {0.1f, 0.1f, 0.1f};
	plight->diffuse  = {0.2f, 0.3f, 0.5f};
	plight->specular = {1.0f, 1.0f, 1.0f};
	plight->attenuation = {0.6f, 0.09f, 0.012f};

	MeshRenderer* mr = point->AddComponent<MeshRenderer>();
	mr->SetMesh(Resources::Get<Mesh>("cube"));
	mr->material->SetColor("ambient_color", Color::white);
	mr->material->SetColor("diffuse_color", Color::white);
	mr->material->SetColor("specular_color", Color::white);
	mr->material->SetFloat("shininess", 24.0f);
	mr->transform->SetLocalScale({0.2f, 0.2f, 0.2f});

	AddEntity<Starship>("Ufo");
	Entity* mah = AddEntity<Starship>("mah");
	mah->transform->SetLocalPosition({4.0f, 2.0f, -1.0f});
	mah->transform->SetLocalRotation({10, 10, 0});
	//return;

	Entity* ground = AddEntity("Ground");

	ground->transform->SetLocalPosition({0.0f, -4.0f, 0.0f});
	Rigidbody2D* groundrb = ground->AddComponent<Rigidbody2D>();
	groundrb->SetType(RigidbodyType::STATIC);
	BoxCollider2D* ec = ground->AddComponent<BoxCollider2D>();
	ec->SetShape({6,0.5f});

	Entity* door = AddEntity("Door");
	door->transform->SetLocalPosition({4.0f, -4.0f, 0.0f});
	Rigidbody2D* doorrb = door->AddComponent<Rigidbody2D>();
	doorrb->SetType(RigidbodyType::STATIC);
	BoxCollider2D* dc = door->AddComponent<BoxCollider2D>();
	dc->SetSensor(true);
	dc->SetShape({0.1,4.0f});

	//ground->transform->SetLocalRotation({0,0,20});

	Pancrazio* pancrazio = AddEntity<Pancrazio>();
	//pancrazio->transform->SetParent(container->transform);
	pancrazio->transform->SetLocalScale({1.0f, 1.0f, 0.0f});
	pancrazio->transform->SetLocalPosition({0.0f, 0.0f, 0.0f});
	//pancrazio->GetComponent<Animation>()->Disable();
	pancrazio->transform->SetLocalRotation({0,0,30});

	pancrazio->AddComponent<Mover>();

	Pancrazio* sonOfPancrazio = AddEntity<Pancrazio>("Son of Pancrazio");
	sonOfPancrazio->setParent(pancrazio);
	//sonOfPancrazio->transform->isFree = true;
	//sonOfPancrazio->GetComponent<Animation>()->Disable();
	//sonOfPancrazio->GetComponent<Mover>()->Disable();
	sonOfPancrazio->transform->SetLocalPosition({-1.0f, 0.0f, 0.0f});
	sonOfPancrazio->transform->SetLocalScale({0.5f, 0.5f, 0.0f});
	sonOfPancrazio->GetComponent<Rigidbody2D>()->SetType(RigidbodyType::STATIC);
	sonOfPancrazio->GetComponent<BoxCollider2D>("box")->ResetShape(); // <---- collegare al transform addirittura? fare dei callback transformChanged
	sonOfPancrazio->GetComponent<BoxCollider2D>("trigger")->ResetShape(); // <---- collegare al transform addirittura? fare dei callback transformChanged
	//sonOfPancrazio->GetComponent<CircleCollider2D>()->ResetShape(); // <---- collegare al transform addirittura? fare dei callback transformChanged
	//sonOfPancrazio->transform->setLocalRotation({0,0,20});

	Entity* bkg = AddEntity("Background");
	//bkg->transform->SetLocalPosition({0.0f, 0.0f, -0.5f});
	SpriteRenderer* backgroundRenderer = bkg->AddComponent<SpriteRenderer>();
	// backgroundRenderer->shader = Resources::Get<Shader>("standard");
	backgroundRenderer->name = "Background Renderer";
	backgroundRenderer->sortingLayerID = Config::SortingLayers["Background"];
	backgroundRenderer->sprite = new Sprite("Background", Resources::Get<Texture>("night"));
	backgroundRenderer->sprite->SetPixelPerUnit(64);
	backgroundRenderer->sprite->Build();

	//Font* f = Resources::Get<Font>("Pixel Perfect");
	Font* f = Resources::Get<Font>("Modenine");

	TextRenderer* text = root->AddComponent<TextRenderer>();
	text->sortingLayerID = Config::SortingLayers["UI"];
	text->SetFont(f)->SetText("HELLO PANCRAZIO!")->SetColor(Color::red)->SetSize(1.0f)->SetOffset({-1.0f, -1.0f});

	/*Design::DrawPolygon({
		 {0.0f, 1.0f, 0.0f},
		 {2.0f, 1.0f, 0.0f},
		 {2.0f, -1.0f, 0.0f},
		 {-1.0f, -1.0f, 0.0f}
	}, Color::red, DrawMode::FULL);*/

}

