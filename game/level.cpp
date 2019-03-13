#include "globals.h"
#include "level.h"
#include "pancrazio.h"
#include "starship.h"
#include "mover.h"

Level::Level() {

	using namespace se;

	/* Entity* directional = AddEntity("Directional");
	directional->transform->SetLocalRotation({20, 10, 0});
	Light* light = directional->AddComponent<Light>();
	light->type = LightType::DIRECTIONAL;
	light->ambient  = {0.2f, 0.2f, 0.2f};
	light->diffuse  = {1.0f, 0.5f, 0.5f};
	light->specular = {1.0f, 1.0f, 1.0f};

	Entity* point = AddEntity("Point 1");
	point->transform->SetLocalPosition({3.0f, 1.7f, 4.0f});
	Light* plight =point->AddComponent<Light>();
	plight->type = LightType::POINT;
	plight->ambient  = {0.3f, 0.3f, 0.3f};
	plight->diffuse  = {0.7f, 0.7f, 0.7f};
	plight->specular = {1.0f, 1.0f, 1.0f};
	plight->attenuation = {0.6f, 0.09f, 0.012f};

	MeshRenderer* mr = point->AddComponent<MeshRenderer>();
	mr->SetMesh(Resources::Get<Mesh>("cube"));
	mr->material->SetColor("ambient_color", Color::white);
	mr->material->SetColor("diffuse_color", Color::white);
	mr->material->SetColor("specular_color", Color::white);
	mr->material->SetFloat("shininess", 20.0f);
	mr->transform->SetLocalScale({0.1f, 0.1f, 0.1f});

	AddEntity<Starship>("Cassa");
	Entity* mah = AddEntity<Starship>("mah");
	mah->transform->SetLocalPosition({4.0f, 2.0f, -1.0f});
	mah->transform->SetLocalRotation({10, 10, 0}); */
	//return;

	//Font* pixel = Resources::Get<Font>("Pixel Perfect");
	Font* f = Resources::Get<Font>("Modenine");

	Entity* label = AddEntity("Label");
	Text* text = label->AddComponent<Text>();
	text->sortingLayerID = Config::SortingLayers["UI"];
	text->SetFont(f)->SetText("Hello game engine!")->SetColor(Color::blue)->SetSize(0.5f);
	text->transform->SetPivot(PivotPosition::TOPLEFT);
	text->transform->rectTransform->SetRectSize({8,3});
	//text->transform->SetLocalScale({2,2,0});
	text->SetAlign(Align::TOPLEFT);

	Entity* canvas = AddEntity<ui::Canvas>("Canvas");
	canvas->GetComponent<Canvas>()->SetRenderMode(RenderMode::SCREEN);

	// Componente text direttamente agganciato alla canvas
	Text* text1 = canvas->AddComponent<Text>();
	text1->sortingLayerID = Config::SortingLayers["Background"];
	text1->SetFont(f)->SetText("CANVAS")->SetColor(Color::red)->SetSize(0.5f);
	text1->SetAlign(Align::TOPLEFT);

	// compoenente text in una child entity
	ui::Text* uiText = AddEntity<ui::Text>("Label su canvas");
	uiText->setParent(canvas);
	uiText->transform->SetPivot(PivotPosition::BOTTOMLEFT);
	uiText->transform->rectTransform->SetRectSize({3,1});
	//uiText->transform->SetLocalPosition({4, 4, 0});
	uiText->transform->SetLocalPosition({1, 1, 0});
	auto tComp = uiText->GetComponent<Text>();
	tComp->SetFont(f)->SetText("Label su canvas")->SetColor(Color::green)->SetSize(0.5f)->SetAlign(Align::BOTTOMLEFT);

	/*Text* text2 = canvasObject->AddComponent<Text>();
	text2->SetFont(f)->SetText("prova 123")->SetColor(Color::red)->SetSize(0.4f);
	text2->transform->SetRect({0,0,10,10});
	text2->SetPivot(Align::CENTER);
	text2->SetAlign(Align::BOTTOM); */

	return;

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

	pancrazio->AddProgram<Mover>();

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

	/*Design::DrawPolygon({
		 {0.0f, 1.0f, 0.0f},
		 {2.0f, 1.0f, 0.0f},
		 {2.0f, -1.0f, 0.0f},
		 {-1.0f, -1.0f, 0.0f}
	}, Color::red, DrawMode::FULL);*/

}

