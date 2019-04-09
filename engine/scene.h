#pragma once

#include <set>
#include <string>

#include "component.h"
#include "debug.h"
#include "entity/debuggrid.h"
#include "debuginfo.h"
#include "entity.h"
#include "gamedata.h"
#include "light.h"
#include "entity/maincamera.h"
#include "renderer.h"
#include "transform.h"
#include "utility.h"

namespace se {

// class Component;
class Camera;
class Cycle;

class Scene {
public:
    friend class Cycle;

    Scene();
    ~Scene();

    std::string name = "";
    int BuildIndex;
    bool isLoaded = false;
    bool invalid = true;

    Entity* root = nullptr;
    Camera* activeCamera = nullptr;
    DebugInfo* debugInfo = nullptr;

    std::multiset<Entity*> Entities;
    std::multiset<Component*, CompareComponent> ActiveComponents;
    std::multiset<Light*> ActiveLights;
    std::multiset<Component*, CompareComponent> ActiveOverlayRenderers;

    void renderOverlay();

    void Invalidate() {
        invalid = true;
    }

    std::multiset<Entity*> GetRootEntitys();

    // scan
    void InitEntities();
    void ScanActiveComponents();
    void SortActiveComponents();
    void ScanActiveLights();
    void ScanActiveRenderers();

    // debug
    void PrintActiveComponentsInScene();
    void PrintActiveRenderersInScene();
    void PrintActiveLightsInScene();
    void PrintHierarchy();

    Entity* RegisterEntity(Entity* entity_);
    Entity* AddEntity(std::string);
    Entity* GetEntity(std::string);
    bool HasEntity(Entity* entity_);

    template <class T>
    T* AddEntity(std::string _name = "") {  // Adds a Entity of class T (Prefab)

        T* entity = new T();
        entity->name = (_name == "" ? util::classtitle<T>() : _name);
        entity->scene = this;
        entity->init();
        entity->transform->SetParent(root->transform);
        Entities.insert(entity);
        entity->registered = true;
        Invalidate();
        return entity;
    }

    template <class T>
    T* GetEntity() {
        for (Entity* entity : Entities) {
            if (dynamic_cast<T*>(entity))
                return dynamic_cast<T*>(entity);
        }
        return nullptr;
    }

    void RemoveEntity(Entity* entity_);

    void UnsetActiveComponent(Component* component);
    void SetActiveComponent(Component* component);

private:
    void init();
    void update();
    void fixed();
    void render();
    void exit();
};

}  // namespace se
