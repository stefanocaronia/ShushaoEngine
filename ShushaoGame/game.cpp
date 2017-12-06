#include <iostream>

#include "globals.h"
#include "game.h"
#include "level.h"

using namespace std;
using namespace glm;

Game::Game(string title) : Cycle(title) {

  	Time::setFrameRateLimit(120.0f);
	Time::setFixedRateLimit(60.0f);

	Config::Layers = {
		"Background",
		"Items"
	};

	Config::SortingLayers = {
		"Background",
		"Characters",
		"Sky"
	};

	Config::displayWidth = 1024;
	Config::displayHeight = Config::displayWidth / (16.0f/9.0f);
	Config::pixelPerUnit = 16;

	Debug::level = DebugLevel::INFO;
	Debug::enabled = true;
	Debug::debugGridMode = GridMode::ORTHOGRAFIC;

	System::Input.printActiveControllers();

	InputMapping* fire = System::Input.addMapping("fire");

	fire->positiveButton = SDL_SCANCODE_LCTRL;
	fire->positiveControllerButton = SDL_CONTROLLER_BUTTON_A;
	fire->mouseButton = SDL_BUTTON_LEFT;

	InputMapping* horizontal = System::Input.addMapping("horizontal");

	horizontal->positiveButton = SDL_SCANCODE_D;
	horizontal->negativeButton = SDL_SCANCODE_A;
	horizontal->altPositiveButton = SDL_SCANCODE_RIGHT;
	horizontal->altNegativeButton = SDL_SCANCODE_LEFT;
	horizontal->controllerAxis = SDL_CONTROLLER_AXIS_LEFTX;
	horizontal->deadZone = 0.2f;
}

Game::~Game() {
   // do
}

void Game::Awake() {

	Resources::Load<Texture>("assets/pancrazio.png");
	Resources::Load<Texture>("assets/night.jpg");
	Resources::Load<Texture>("assets/pancsmile.png");
	Resources::Load<TextureAtlas>("assets/walking.png")->AddGrid(vec2(16,16), PivotPosition::BOTTOM);
	Resources::Load<Shader>("shaders/standard");
	Resources::Add<Sprite>("pancrazio_sprite")->setTexture(Resources::Get<Texture>("pancrazio"));

	Resources::Add<SpriteSheet>("walking")->Load(Resources::Get<TextureAtlas>("walking"));

	SceneManager::LoadScene<Level>("Level 1");

	Camera* camera = SceneManager::activeScene->activeCamera;
	camera->backgroundColor = {0.2f, 0.2f, 0.8f, 1.0f};
	camera->setOrthographic(true);
	camera->setNearClipPlane(12.0f);
	camera->setFarClipPlane(1.0f);
	camera->setOrthographicSize(5.0f);

	camera->transform->localPosition = {0.0f, 0.0f, 10.0f};
	camera->transform->localRotation = Transform::QUATERNION_IDENTITY;

	if (Debug::enabled) {
		SceneManager::activeScene->PrintHierarchy();
		SceneManager::activeScene->PrintActiveComponentsInScene();
		SceneManager::activeScene->PrintActiveRenderersInScene();
		System::ListServices();
		camera->print();
		Resources::toString();
		Config::Layers.toString("Layers");
		Config::SortingLayers.toString("SortingLayers");
	}
}

void Game::Start() {

}

void Game::FixedUpdate() {

}

void Game::Update() {

}

void Game::Render() {

}

void Game::End() {

}

void Game::Input() {
	if (System::Input.getButton("fire")) {
		Debug::Log << "FIRE!" << endl;
	}

	double horizontal = System::Input.getAxis("horizontal");
	if (horizontal != 0) {
		Debug::Log << horizontal << endl;
	}
}
