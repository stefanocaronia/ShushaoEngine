#include "globals.h"
#include "level.h"
#include "pancrazio.h"
#include "mover.h"

Level::Level() {

	using namespace se;

	Entity* ground = AddEntity("Ground");
	//Entity* container = AddEntity("Container");

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

	SpriteRenderer* backgroundRenderer = root->AddComponent<SpriteRenderer>();
	// backgroundRenderer->shader = Resources::Get<Shader>("standard");
	backgroundRenderer->name = "Background Renderer";
	backgroundRenderer->sortingLayerID = Config::SortingLayers["Background"];
	backgroundRenderer->sprite = new Sprite("Background", Resources::Get<Texture>("night"));
	backgroundRenderer->sprite->SetPixelPerUnit(64);

	// Font* modenine = Resources::Get<Font>("Modenine");
	// modenine->setSize(24);

	// TextRenderer* text = pancrazio->AddComponent<TextRenderer>();
	// text->SetFont(modenine);
	// text->name = "Text Test";
	// text->sortingLayerID = Config::SortingLayers["UI"];
	// text->SetText("Hello Pancrazio!");

	/*Design::DrawPolygon({
		 {0.0f, 1.0f, 0.0f},
		 {2.0f, 1.0f, 0.0f},
		 {2.0f, -1.0f, 0.0f},
		 {-1.0f, -1.0f, 0.0f}
	}, Color::red, DrawMode::HOLLOW);*/
}

