#include <core_.h>
#include <std_.h>

#include "config.h"
#include "cycle.h"
#include "debug.h"
#include "design.h"
#include "font.h"
#include "glmanager.h"
#include "input.h"
#include "physics/physics.h"
#include "resources.h"
#include "scenemanager.h"
#include "system.h"

se::Cycle* GAME;

namespace se {

Cycle::Cycle() {
    GAME = this;
}

Cycle::~Cycle() {
    Debug::Log << "Cycle Destructor" << std::endl;
}

bool Cycle::init() {
    for (bool& k : keys) {
        k = false;
    }

    // Load engine configuration files
    if (!Config::LoadEngineConfig()) {
        Debug::Log(ERROR) << "Error Initializing Engine Configuration" << std::endl;
        ::exit(5);
    }

    // Load user configuration files
    if (!Config::LoadUserConfig()) {
        Debug::Log(ERROR) << "Error Initializing User Configuration" << std::endl;
    }

    // Load configuration overrides
    if (!InitConfig()) {
        Debug::Log(ERROR) << "Error Initializing Configuration overrides" << std::endl;
    }

    // OpenGL Context init
    if (!GLManager::Init(Config::title, Config::fullscreen)) {
        Debug::Log(ERROR) << "Error Initializing GL" << std::endl;
        ::exit(5);
    }

    // load resoruces (derived)
    if (!InitResources()) {
        Debug::Log(ERROR) << "Error loading resources" << std::endl;
    }

    // engine resources
    Resources::Load<Font>("consolas", FONT_CONSOLAS, LIB_SHUSHAO);

    // Time init
    Time::setFrameRateLimit(Config::Time::frameRateLimit);
    Time::setFixedRateLimit(Config::Time::fixedRateLimit);

    // Physics 2d init
    if (Config::Physics::enabled) {
        if (!Physics::init()) {
            Debug::Log(ERROR) << "Error Initializing Physics" << std::endl;
        }
    }
    // Init Input service
    Input::init();

    // Init System services
    System::init();

    // Init input mappings (derived)
    if (!InitMapping()) {
        Debug::Log(ERROR) << "Error In input mapping" << std::endl;
    }

    // init and load starting scene (derived)
    if (!InitScene()) {
        Debug::Log(ERROR) << "Error Initializing Scene" << std::endl;
    }

    // Awake method (derived)
    Awake();

    // init all entities
    SceneManager::activeScene->ScanEntities();
    SceneManager::activeScene->ScanActiveComponents();

    SceneManager::activeScene->init();  // vengono chiamati qui gli Awake di tutti gli oggetti attivi

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

    while (RUNNING) {
        Time::Update();

        std::thread tInput;
        std::thread tUpdate;
        std::thread tFixed;

        // scan scene (se invalid) e init objects
        initscan();

        // Process input method (derived)
        //tInput = std::thread(&Cycle::GetInput, this);
        GetInput();

        // Update Cycle
        //tUpdate = std::thread(&Cycle::update, this);
        update();

        if (Time::fixedDeltaTime >= Time::fixedLimitDuration) {
            // Fixed Update Cycle (physics)
            //tFixed = std::thread(&Cycle::fixed, this);
            fixed();
        }

        if (tInput.joinable()) tInput.join();
        if (tUpdate.joinable()) tUpdate.join();
        if (tFixed.joinable()) tFixed.join();

        if (Config::Time::frameRateLimit == 0 || (Time::renderDeltaTime >= Time::frameLimitDuration)) {
            // Main render cycle
            render();
        }
    }

    exit();
}

void Cycle::stop() {
    RUNNING = false;
}

void Cycle::initscan() {
    if (SceneManager::activeScene->invalid) {
        SceneManager::activeScene->ScanEntities();
        SceneManager::activeScene->ScanActiveComponents();
    }

    // chiamo awake di tutti i componenti non ancora svegli
    SceneManager::activeScene->init();
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
    Input::update();  // Update Input Service
    System::update();  // update dei system services
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
