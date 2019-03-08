#include <iostream>

#include "globals.h"
#include "game.h"
#include "level.h"

	using namespace std;
	using namespace glm;
	using namespace se;

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
		"Sky",
		"UI"
	};

	Config::displayWidth = 1024;
	Config::displayHeight = Config::displayWidth / (16.0f/9.0f);
	Config::pixelPerUnit = 128;

	Debug::level = DebugLevel::INFO;
	Debug::enabled = true;
	Debug::debugGridMode = GridMode::PERSPECTIVE;
	Config::Physics::debug = true;
}

void Game::Awake() {

	Resources::Load<Texture>("assets/pancrazio.png");
	Resources::Load<Texture>("assets/night.jpg");
	Resources::Load<Texture>("assets/pancsmile.png");
	Resources::Load<TextureAtlas>("assets/walking.png")->AddGrid(vec2(16, 16), PivotPosition::BOTTOM);
	Resources::Add<Sprite>("pancrazio_sprite")->SetTexture(Resources::Get<Texture>("pancrazio"))->SetPixelPerUnit(16)->Build();

	Resources::Load<Mesh>("assets/cube.obj");
	Resources::Load<Texture>("assets/cube_diffuse.png");
	Resources::Load<Texture>("assets/tap.jpg");

	Resources::Load<Music>("assets/fizz.mp3");
	Resources::Load<Effect>("assets/hit.wav");
	Resources::Load<Effect>("assets/shoot.wav")->setVolume(40);

	// Resources::Add<SpriteSheet>("walking")->Load(Resources::Get<TextureAtlas>("walking"));

	Resources::Load<Font>("assets/modenine.ttf", "Modenine");
	Resources::Load<Font>("assets/pixelperfect.ttf", "Pixel Perfect");

	SceneManager::LoadScene<Level>("Level 1");

	bool meshTest = true;

	Camera* camera = SceneManager::activeScene->activeCamera;
	camera->backgroundColor = {0.05f, 0.05f, 0.2f, 1.0f};

	if (meshTest) {
		camera->setOrthographic(false);
		camera->setFarClipPlane(20.0f);
		camera->transform->localPosition = {1.0f, 3.0f, 6.0f};
		camera->transform->localRotation = Transform::QUATERNION_IDENTITY;
	} else {
		camera->setOrthographic(true);
		camera->setNearClipPlane(12.0f);
		camera->setFarClipPlane(1.0f);
		camera->setOrthographicSize(5.0f);
		camera->transform->localPosition = {0.0f, 0.0f, 10.0f};
		camera->transform->localRotation = Transform::QUATERNION_IDENTITY;
	}

	Input::printActiveControllers();

	InputMapping* fire = Input::addMapping("fire");

	fire->type = InputType::BUTTON;
	fire->positiveButton = SDL_SCANCODE_LCTRL;
	fire->positiveControllerButton = SDL_CONTROLLER_BUTTON_A;
	fire->mouseButton = SDL_BUTTON_LEFT;

	InputMapping* fire2 = Input::addMapping("fire2");

	fire2->type = InputType::BUTTON;
	fire2->positiveButton = SDL_SCANCODE_RCTRL;
	fire2->positiveControllerButton = SDL_CONTROLLER_BUTTON_Y;
	fire2->mouseButton = SDL_BUTTON_RIGHT;

	InputMapping* horizontal = Input::addMapping("horizontal");

	horizontal->type = InputType::AXIS;
	horizontal->positiveButton = SDL_SCANCODE_D;
	horizontal->negativeButton = SDL_SCANCODE_A;
	horizontal->altPositiveButton = SDL_SCANCODE_RIGHT;
	horizontal->altNegativeButton = SDL_SCANCODE_LEFT;
	horizontal->controllerAxis = SDL_CONTROLLER_AXIS_LEFTX;
	horizontal->deadZone = 0.2f;

	if (Debug::enabled) {
		SceneManager::activeScene->PrintHierarchy();
		SceneManager::activeScene->PrintActiveComponentsInScene();
		SceneManager::activeScene->PrintActiveRenderersInScene();
		SceneManager::activeScene->PrintActiveLightsInScene();
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

void Game::GetInput() {

	if ((Input::getKey(SDL_SCANCODE_LCTRL) && Input::getKeyDown(SDL_SCANCODE_Q)) || Input::getKeyDown(SDL_SCANCODE_ESCAPE))
		stop();

	// WINDOW
	if (Input::getKeyDown(SDL_SCANCODE_F11))
		GLManager::ToggleFullscreen();

	if (Input::getButtonDown("fire")) {
		Debug::Log << "FIRE!" << endl;
		Resources::Get<Effect>("shoot")->play();
	}

	if (Input::getButtonDown("fire2")) {
		Debug::Log << "FIRE 2!" << endl;
		Resources::Get<Effect>("hit")->play();
	}

	double horizontal = Input::getAxis("horizontal");
	if (horizontal != 0) {
		Debug::Log << horizontal << endl;
	}

	if (Input::getKeyDown(SDL_SCANCODE_D)) {
		Debug::enabled = !Debug::enabled;
	}

	if (Input::getKeyDown(SDL_SCANCODE_F)) {
		Config::Physics::debug = !Config::Physics::debug;
	}

	if (Input::getKeyDown(SDL_SCANCODE_P)) {
		if (Music::isPlaying()) {
			Debug::Log << "PAUSE" << endl;
			Music::pause();
		} else if (Music::isPaused()) {
			Debug::Log << "RESUME" << endl;
			Music::resume();
		} else {
			Debug::Log << "PLAY" << endl;
			Resources::Get<Music>("fizz")->play(-1);
		}
	} else if (Input::getKeyDown(SDL_SCANCODE_O)) {
		Debug::Log << "STOP" << endl;
		Music::stop();
	} else if (Input::getKeyDown(SDL_SCANCODE_M)) {
		if (!Music::isMuted()) {
			Debug::Log << "MUTE" << endl;
			Music::mute();
		} else {
			Debug::Log << "UNMUTE" << endl;
			Music::unMute();
		}
	}

	if (Input::getKey(SDL_SCANCODE_I)) {
        Debug::Log << Music::addVolume(1) << endl;
	} else if (Input::getKey(SDL_SCANCODE_U)) {
		Debug::Log << Music::addVolume(-1) << endl;
	}

	if (Input::getKey(SDL_SCANCODE_C)) {
		vec3 pos = SceneManager::activeScene->activeCamera->transform->position;
		SceneManager::activeScene->activeCamera->transform->SetLocalPosition({
			pos.x - (2.4f * Time::deltaTime), pos.y, pos.z
		});
	} else if (Input::getKey(SDL_SCANCODE_V)) {
		vec3 pos = SceneManager::activeScene->activeCamera->transform->position;
		SceneManager::activeScene->activeCamera->transform->SetLocalPosition({
			pos.x + (2.4f * Time::deltaTime), pos.y, pos.z
		});
	}

}
