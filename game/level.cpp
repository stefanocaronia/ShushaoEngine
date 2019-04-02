#include "globals.h"
#include "level.h"
#include "pancrazio.h"
#include "starship.h"
#include "mover.h"
#include "hermite.h"
#include "part.h"
#include "meshtest.h"

Level::Level() {

	using namespace se;

	AddEntity<Part>("Particle Object");
	// AddEntity<Hermite>();
	// AddEntity<Meshtest>();

	return;

	Font* f = Resources::Get<Font>("Modenine");

	Entity* label = AddEntity("Label");
	Text* text = label->AddComponent<Text>();
	text->sortingLayerID = Config::SortingLayers["UI"];
	text->alignToGeometry = true;
	text->SetFont(f)->SetText("Hello game engine!")->SetColor(color::blue)->SetSize(0.5f);
	text->transform->SetPivot(PivotPosition::TOPLEFT);
	text->transform->rectTransform->SetRectSize({8,3});
	text->transform->SetLocalPosition({5, -1, 0});
	//text->transform->SetLocalScale({2,2,0});
	text->SetAlign(Align::TOPLEFT);

	Camera* screenSpaceCamera = root->AddComponent<Camera>("Screen Space Camera");
	screenSpaceCamera->setOrthographic(true);
	screenSpaceCamera->setNearClipPlane(12.0f);
	screenSpaceCamera->setFarClipPlane(-1.0f);
	screenSpaceCamera->setOrthographicSize(5.0f);
	screenSpaceCamera->transform->localPosition = {0.0f, 0.0f, 10.0f};
	screenSpaceCamera->transform->localRotation = Transform::QUATERNION_IDENTITY;

	Entity* canvas = AddEntity<ui::Canvas>("Canvas");

	canvas->GetComponent<Canvas>()->SetCamera(screenSpaceCamera)->SetRenderMode(RenderMode::WORLD);
	canvas->transform->rectTransform->SetRectSize({10, 4});
	canvas->transform->SetLocalPosition({-1, 0, 0});
	canvas->transform->SetPivot(PivotPosition::CENTER);
	// Componente text direttamente agganciato alla canvas
	Text* text1 = canvas->AddComponent<Text>();
	text1->alignToGeometry = true;
	text1->sortingLayerID = Config::SortingLayers["Background"];
	text1->SetFont(f)->SetText("TL")->SetColor(color::red)->SetSize(0.5f);
	text1->SetAlign(Align::TOPLEFT);
	Text* text2 = canvas->AddComponent<Text>();
	text2->alignToGeometry = true;
	text2->sortingLayerID = Config::SortingLayers["Background"];
	text2->SetFont(f)->SetText("TR")->SetColor(color::red)->SetSize(0.5f);
	text2->SetAlign(Align::TOPRIGHT);
	Text* text3 = canvas->AddComponent<Text>();
	text3->alignToGeometry = true;
	text3->sortingLayerID = Config::SortingLayers["Background"];
	text3->SetFont(f)->SetText("BR")->SetColor(color::red)->SetSize(0.5f);
	text3->SetAlign(Align::BOTTOMRIGHT);
	Text* text4 = canvas->AddComponent<Text>();
	text4->alignToGeometry = true;
	text4->sortingLayerID = Config::SortingLayers["Background"];
	text4->SetFont(f)->SetText("BL")->SetColor(color::red)->SetSize(0.5f);
	text4->SetAlign(Align::BOTTOMLEFT);
	Text* text5 = canvas->AddComponent<Text>();
	text5->alignToGeometry = true;
	text5->sortingLayerID = Config::SortingLayers["Background"];
	text5->SetFont(f)->SetText("CE")->SetColor(color::red)->SetSize(0.5f);
	text5->SetAlign(Align::CENTER);

	// compoenente text in una child entity
	ui::Text* uiText = AddEntity<ui::Text>("Label su canvas");
	uiText->setParent(canvas);
	uiText->transform->SetPivot(PivotPosition::BOTTOMLEFT);
	uiText->transform->rectTransform->SetAnchor(AnchorPreset::CENTER);
	uiText->transform->rectTransform->SetRectSize({2, 1});
	uiText->transform->SetLocalPosition({-2, -2, 0});
	uiText->transform->SetPivot(PivotPosition::BOTTOMRIGHT);
	auto tComp = uiText->GetComponent<Text>();
	tComp->wordWrap = false;
	tComp->SetFont(f)->SetText("Label su canvas")->SetColor(color::green)->SetSize(0.5f)->SetAlign(Align::BOTTOMRIGHT);

	// compoenente text in una child entity - ancorata diversamente
	ui::Text* anchoredText = AddEntity<ui::Text>("Label 2");
	anchoredText->setParent(canvas);
	anchoredText->transform->SetPivot(PivotPosition::CENTER);

	anchoredText->transform->rectTransform->SetAnchor(AnchorPreset::TOPSTRETCH);
	anchoredText->transform->rectTransform->RegisterPositionLRYH(1.0f, 1.0f, -1.0f, 1.0f);

	/* anchoredText->transform->rectTransform->SetAnchor(AnchorPreset::STRETCH);
	anchoredText->transform->rectTransform->RegisterPositionLRTB(1.0f, 1.0f, 1.0f, 1.0f); */

	/* anchoredText->transform->rectTransform->SetAnchorMax({1, 1});
	anchoredText->transform->rectTransform->SetAnchorMin({0, 0});
	anchoredText->transform->rectTransform->RegisterPositionLRTH(1.0f, 1.0f, 1.0f, 4.0f); */

	/* anchoredText->transform->rectTransform->SetAnchorMax({0, 1});
	anchoredText->transform->rectTransform->SetAnchorMin({0, 0});
	anchoredText->transform->rectTransform->RegisterPositionTBXW(1.0f, 1.0f, 2.0f, 3.0f); */

	auto t = anchoredText->GetComponent<Text>();
	t->SetFont(f)->SetText("Con punti ancoraggio")->SetColor(color::yellow)->SetSize(0.3f)->SetAlign(Align::CENTER);

	/* ui::RawImage* uiImage = AddEntity<ui::RawImage>("Immagine su canvas");
	uiImage->setParent(canvas);

	RawImage* image1 = uiImage->GetComponent<RawImage>();
	image1->SetTexture(Resources::Get<Texture>("avatar"));
	image1->transform->rectTransform->SetAnchorMax({1, 1});
	image1->transform->rectTransform->SetAnchorMin({0, 0});
	image1->transform->rectTransform->RegisterPositionLRTB(1.0f, 1.0f, 1.0f, 1.0f);
	image1->SetUvRect({0.0f, 0.0f, 1.0f, 1.0f})->SetColor({0.5f, 0.1f, 0.1f, 0.4f});
	image1->sortingLayerID = Config::SortingLayers["UI"]; */

	//ui::Image* uiImage2 = AddEntity<ui::Image>("Immagine su canvas");
	//uiImage2->setParent(canvas);
//
	//Image* image2 = uiImage2->GetComponent<Image>();
	//image2->SetSprite(Resources::Get<Sprite>("eye_sprite"));
	///* image2->transform->rectTransform->SetAnchor({0.5f, 0.5f});
	//image2->transform->rectTransform->SetRectSize({6, 3});
	//image2->transform->SetLocalPosition({3, 1, 0});*/
	//image2->transform->rectTransform->SetAnchorMax({1, 1});
	//image2->transform->rectTransform->SetAnchorMin({0, 0});
	//image2->transform->rectTransform->RegisterPositionLRTB(1.0f, 1.0f, 1.0f, 1.0f);
	//image2->sortingLayerID = Config::SortingLayers["UI"];
	// image2->SetPreserveAspect(false);

	ui::Image* sliced = AddEntity<ui::Image>("Immagine sliced");
	sliced->setParent(canvas);

	Image* imagesl = sliced->GetComponent<Image>();
	imagesl->SetSprite(Resources::Get<Sprite>("dialog_sprite"));
	imagesl->transform->rectTransform->SetAnchor(AnchorPreset::STRETCH);
	imagesl->transform->rectTransform->RegisterPositionLRTB(1.0f, 1.0f, 1.0f, 1.0f);
	imagesl->sortingLayerID = Config::SortingLayers["UI"];
	imagesl->SetPreserveAspect(false)->SetImageType(Image::Type::TILED)->SetBorder({40,40,40,40})->SetFillCenter(false);

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
	}, color::red, DrawMode::FULL);*/

}

