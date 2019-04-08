#include <chrono>
#include <iostream>
#include <string>

#include "config.h"
#include "cycle.h"
#include "debug.h"
#include "design.h"
#include "glmanager.h"
#include "input.h"
#include "physics/physics.h"
#include "resources.h"
#include "scenemanager.h"
#include "stime.h"
#include "system.h"
#include "font.h"

se::Cycle* GAME;

namespace se {

using namespace std;

Cycle::Cycle() {
    GAME = this;
}

Cycle::~Cycle() {
    Debug::Log << "Cycle Destructor" << endl;
}

bool Cycle::init() {
    for (bool& k : keys) {
        k = false;
    }

    // Load engine configuration files
    if (!Config::LoadEngineConfig()) {
        Debug::Log(ERROR) << "Error Initializing Engine Configuration" << endl;
        ::exit(5);
    }

    // Load user configuration files
    if (!Config::LoadUserConfig()) {
        Debug::Log(ERROR) << "Error Initializing User Configuration" << endl;
    }

    // Load configuration overrides
    if (!InitConfig()) {
        Debug::Log(ERROR) << "Error Initializing Configuration overrides" << endl;
    }

    // OpenGL Context init
    if (!GLManager::Init(Config::title, Config::fullscreen)) {
        Debug::Log(ERROR) << "Error Initializing GL" << endl;
        ::exit(5);
    }

    // Time init
    Time::setFrameRateLimit(Config::Time::frameRateLimit);
    Time::setFixedRateLimit(Config::Time::fixedRateLimit);

    // Physics 2d init
    if (Config::Physics::enabled) {
        if (!Physics::init()) {
            Debug::Log(ERROR) << "Error Initializing Physics" << endl;
        }
    }

    // Init Input service
    Input::init();

    // Init System services
    System::init();

    // load resoruces (derived)
    if (!InitResources()) {
        Debug::Log(ERROR) << "Error loading resources" << endl;
    }

    // engine resources
    Resources::Load<Font>("consolas", FONT_CONSOLAS, LIB_SHUSHAO);

    // Init input mappings (derived)
    if (!InitMapping()) {
        Debug::Log(ERROR) << "Error In input mapping" << endl;
    }

    // init and load starting scene (derived)
    if (!InitScene()) {
        Debug::Log(ERROR) << "Error Initializing Scene" << endl;
    }

    // init all entities
    SceneManager::activeScene->InitEntities();

    // Awake method (derived)
    Awake();

    SceneManager::activeScene->ScanActiveComponents();
    SceneManager::activeScene->ScanActiveLights();
    SceneManager::activeScene->init(); // vengono chiamati qui gli Awake di tutti gli oggetti attivi

    // FIXME: rifaccio lo scan per le cose instanziate in awake dalgi oggetti
    // FIXME: per lo scan active components devo adottare un metodo "invalidate", si invalida la lista components quando si aggiungono components o si abilitano o disabilitano. ora vado a dormire
    SceneManager::activeScene->ScanActiveComponents();
    SceneManager::activeScene->ScanActiveLights();

    if (Debug::enabled) {
        SceneManager::activeScene->PrintHierarchy();
        SceneManager::activeScene->PrintActiveComponentsInScene();
        SceneManager::activeScene->PrintActiveRenderersInScene();
        SceneManager::activeScene->PrintActiveLightsInScene();
        System::ListServices();
        SceneManager::activeScene->activeCamera->print();
        Resources::toString();
        Config::Layers.toString("Layers");
        Config::SortingLayers.toString("SortingLayers");
    }

    Camera* activeCamera = SceneManager::activeScene->activeCamera;

    GLManager::SetFullscreen(Config::fullscreen);
    GLManager::Clear(activeCamera->backgroundColor.r, activeCamera->backgroundColor.g, activeCamera->backgroundColor.b, 1.0f, 1.0f);

    return true;
}

void Cycle::run() {
    if (!SceneManager::sceneSet)
        return;

    // Start method (derived)
    Start();

    double updateStartTime = 0.0f;
    double renderStartTime = 0.0f;

    // MAIN LOOP
    while (RUNNING) {
        Time::Update();

        if (Debug::enabled && Debug::infoEnabled) {
            updateStartTime = 0.0f;
        }

        SceneManager::activeScene->ScanActiveComponents();
        SceneManager::activeScene->ScanActiveLights();

        // Update Input Service
        Input::update();

        // Process input method (derived)
        GetInput();

        System::update();
        update();

        if (Time::fixedDeltaTime >= Time::fixedLimitDuration) {
            fixed();
        }

        if (Debug::enabled && Debug::infoEnabled) {
            SceneManager::activeScene->debugInfo->updateTime = Time::time - updateStartTime;
            renderStartTime = 0.0f;
        }

        if (Time::renderDeltaTime >= Time::frameLimitDuration) {
            render();
        }

        if (Debug::enabled && Debug::infoEnabled) {
            SceneManager::activeScene->debugInfo->renderTime = Time::time - renderStartTime;
            SceneManager::activeScene->debugInfo->frameRate = 1.0 / Time::deltaTime;
        }

        SceneManager::activeScene->componentsScanned = false;
    }

    exit();
}

void Cycle::stop() {
    RUNNING = false;
}

void Cycle::render() {
    Time::renderTime = Time::GetTime();
    GLManager::Reset();
    SceneManager::activeScene->render();
    Render();  // (derived)
    if (Physics::enabled && Physics::debug) Physics::world->DrawDebugData();
    SceneManager::activeScene->renderOverlay();
    Time::frameCount++;
    GLManager::Swap();
}

void Cycle::update() {
    Time::realtimeSinceStartup = Time::GetTime();
    GLManager::Update();
    SceneManager::activeScene->update();
    Update();  // (derived)
}

void Cycle::fixed() {
    Time::fixedTime = Time::GetTime();
    Time::inFixedTimeStep = true;
    if (Physics::enabled) Physics::update();
    SceneManager::activeScene->fixed();
    FixedUpdate();  // (derived)
    Time::inFixedTimeStep = false;
}

void Cycle::exit() {
    End();  // (derived)
    SceneManager::activeScene->exit();
    Input::exit();
    System::exit();
    Physics::exit();
    SceneManager::Clear();
    Resources::Clear();
    System::Clear();
    GLManager::Quit();
}

}  // namespace se
