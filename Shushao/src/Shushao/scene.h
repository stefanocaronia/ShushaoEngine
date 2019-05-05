#pragma once

#include "Shushao/Core.h"
#include "sepch.h"

#include "component.h"
#include "debuginfo.h"
#include "entity.h"
#include "entity/debuggrid.h"
#include "entity/maincamera.h"
#include "gamedata.h"
#include "light.h"
#include "renderer.h"
#include "transform.h"
#include "utility.h"

namespace se {

// class Component;
class Camera;
class Application;

class SHUSHAO_API Scene {
public:
    friend class Application;

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
    void ScanEntities();
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
        RegisterEntity(entity);
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

    void UnregisterEntity(Entity* entity_);

    void RegisterActiveComponent(Component* component);
    void UnregisterActiveComponent(Component* component);

private:
    void init();
    void update();
    void fixed();
    void render();
    void exit();
};

}  // namespace se
