#include <stdlib.h>
#include <windows.h>
#include <iostream>
#include <typeinfo>
#include <vector>

#include "cycle.h"
#include "debuginfo.h"
#include "scene.h"
#include "ui/canvas.h"

namespace se {

using namespace std;

Scene::Scene() {
    name = "Scene";

    // root va istanziata manualmente a questo livello
    root = new Entity("ROOT");
    root->scene = this;
    root->transform = root->AddComponent<Transform>();
    root->transform->isRoot = true;
    root->awaken = true;
    Entities.insert(root);
    root->registered = true;

    MainCamera* mainCameraObj = AddEntity<MainCamera>();
    activeCamera = mainCameraObj->camera;
    GameData::activeCamera = activeCamera;

    if (Debug::enabled) {
        if (Debug::gridEnabled) {
            AddEntity<DebugGrid>("Debug Grid");
        }

        if (Debug::infoEnabled) {
            ui::Canvas* di = AddEntity<ui::Canvas>("Debug Info");
            di->canvas->SetRenderMode(RenderMode::SCREEN);
            debugInfo = di->AddComponent<DebugInfo>();
        }
    }
}

Scene::~Scene() {
    for (Entity* pGO : Entities) {
        delete (pGO);
    }
    delete (root);
    Entities.clear();
}

bool Scene::HasEntity(Entity* entity_) {
    return Entities.empty() || Entities.find(entity_) != Entities.end();
}

Entity* Scene::AddEntity(string _name = "Entity") {
    Entity* entity = new Entity();
    entity->name = _name;
    entity->scene = this;
    entity->init();
    entity->transform->SetParent(root->transform);
    Entities.insert(entity);
    entity->registered = true;
    return entity;
}

Entity* Scene::GetEntity(std::string name_) {
    for (Entity* entity : Entities) {
        if (entity->name == name_)
            return entity;
    }
    return nullptr;
}

void Scene::ScanActiveComponents() {
    ActiveComponents.clear();
    ActiveOverlayRenderers.clear();

    // ottengo i component attivi
    ActiveComponents = root->transform->GetActiveComponentsInChildren();

    for (Component* component : ActiveComponents) {
        Renderer* renderer = dynamic_cast<Renderer*>(component);
        if (renderer != nullptr && renderer->overlay)
            ActiveOverlayRenderers.insert(component);
    }

    ActiveLights.clear();
    for (Component* component : ActiveComponents) {
        if (dynamic_cast<Light*>(component)) {
            ActiveLights.insert((Light*)component);
        }
    }
    invalid = false;
}

void Scene::InitEntities() {
    // ottengo tutte le entities, anche child
    set<Entity*> entities = root->transform->GetEntitiesInChildren();

    for (auto& entity : Entities) {
        if (!entity->awaken) {
            entity->init();
        }
        if (!entity->registered) {
            Entities.insert(entity);
            entity->registered = true;
        }
    }
    invalid = false;
}

void Scene::PrintActiveComponentsInScene() {
    ScanActiveComponents();
    if (!Debug::enabled) return;
    Logger::setColor(ConsoleColor::DARKCYAN);
    std::cout << " Scene " << name << " Active Components:" << std::endl;
    for (Component* component : ActiveComponents) {
        std::cout << "  - " << component->getTitle() << " (" << component->entity->name << ")" << std::endl;
    }
    Logger::setColor(ConsoleColor::LIGHTGREY);
}

void Scene::PrintActiveLightsInScene() {
    if (!Debug::enabled) return;
    Logger::setColor(ConsoleColor::PINK);
    std::cout << " Scene " << name << " Active Lights:" << std::endl;
    for (Light* light : ActiveLights) {
        std::cout << "  - " << light->GetTypeDesc() << " light " << light->getTitle() << " (" << light->entity->name << ")" << std::endl;
    }
    Logger::setColor(ConsoleColor::LIGHTGREY);
}

void Scene::PrintActiveRenderersInScene() {
    ScanActiveComponents();
    if (!Debug::enabled) return;
    Logger::setColor(ConsoleColor::DARKPURPLE);
    std::cout << " Scene " << name << " Active Renderers:" << std::endl;
    for (Component* component : ActiveComponents) {
        if (!dynamic_cast<Renderer*>(component)) continue;
        int layerID = ((Renderer*)component)->sortingLayerID;
        std::cout << "  - "
                  << "[" << Config::SortingLayers[layerID] << " (" << layerID << ")"
                  << ", " << component->sortingOrder << "] " << component->getTitle() << " (" << component->entity->name << ")" << std::endl;
    }
    std::cout << " Scene " << name << " Active Overlay Renderers:" << std::endl;
    for (Component* component : ActiveOverlayRenderers) {
        if (!dynamic_cast<Renderer*>(component)) continue;
        int layerID = ((Renderer*)component)->sortingLayerID;
        std::cout << "  - "
                  << "[" << Config::SortingLayers[layerID] << " (" << layerID << ")"
                  << ", " << component->sortingOrder << "] " << component->getTitle() << " (" << component->entity->name << ")" << std::endl;
    }
    Logger::setColor(ConsoleColor::LIGHTGREY);
}

void Scene::init() {
    for (Component* component : ActiveComponents) {
        if (component != nullptr && !component->awaken) component->init();
    }
}

void Scene::update() {
    for (Component* component : ActiveComponents) {
        if (component != nullptr) component->update();
    }
}

void Scene::fixed() {
    for (Component* component : ActiveComponents) {
        if (component != nullptr) component->fixed();
    }
}

void Scene::render() {
    for (Component* component : ActiveComponents) {
        Renderer* renderer = dynamic_cast<Renderer*>(component);
        if (renderer != nullptr && !renderer->overlay) {  // non eseguo il rendering degli overlay in questo ciclo
            component->render();
        }
    }
}

void Scene::exit() {
    for (Component* component : ActiveComponents) {
        if (component != nullptr) component->exit();
    }
}

void Scene::renderOverlay() {
    for (Component* component : ActiveOverlayRenderers) {
        if (component != nullptr) component->render();
    }
}

void Scene::PrintHierarchy() {
    if (!Debug::enabled) return;
    Logger::setColor(ConsoleColor::GREEN);
    std::cout << " Scene " << name << "" << std::endl;
    root->PrintHierarchy(0);
    Logger::setColor(ConsoleColor::LIGHTGREY);
}

multiset<Entity*> Scene::GetRootEntitys() {
    // TODO: I GAMEOBJECT CON PARENT ROOT
    return Entities;
}

Entity* Scene::RegisterEntity(Entity* entity_) {
    if (entity_ == nullptr) return nullptr;

    if (HasEntity(entity_)) {
        return entity_;
    }

    entity_->scene = this;
    Entities.insert(entity_);
    entity_->registered = true;
    Invalidate();
    return entity_;
}

void Scene::RemoveEntity(Entity* entity_) {
    if (HasEntity(entity_)) {
        Entities.erase(entity_);
    }
}

void Scene::UnsetActiveComponent(Component* component) {
    if (ActiveComponents.empty()) {
        return;
    }

    auto it = ActiveComponents.find(component);
    if (it != ActiveComponents.end()) {
        ActiveComponents.erase(it);
    }

    auto it2 = ActiveOverlayRenderers.find(component);
    if (it2 != ActiveOverlayRenderers.end()) {
        ActiveOverlayRenderers.erase(it2);
    }

    auto it3 = ActiveLights.find((Light*)component);
    if (it3 != ActiveLights.end()) {
        ActiveLights.erase(it3);
    }
}

void Scene::SetActiveComponent(Component* component) {
    if (!ActiveComponents.empty()) {
        auto it = ActiveComponents.find(component);
        if (it != ActiveComponents.end()) {
            return;
        }
    }

    ActiveComponents.insert(component);

    Renderer* renderer = dynamic_cast<Renderer*>(component);
    if (renderer != nullptr && renderer->overlay) {
        ActiveOverlayRenderers.insert(component);
    }

    if (dynamic_cast<Light*>(component)) {
        ActiveLights.insert((Light*)component);
    }
}


}  // namespace se
