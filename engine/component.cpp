#include <algorithm>

#include "component.h"
#include "cycle.h"
#include "debug.h"
#include "entity.h"
#include "gamedata.h"
#include "physics/collider2d.h"
#include "physics/collision2d.h"
#include "renderer.h"
#include "stime.h"
#include "transform.h"
#include "utility.h"

namespace se {

Component::Component() {
    name = getTitle();
    enabled = true;
    GameData::RegisterComponent(this);
}

Component::~Component() {
    Debug::Log << "Component Destructor: " << name << " di " << entity->name << endl;
    exit();
}

void Component::Enable() {
    enabled = true;
    OnEnable();
}

void Component::Disable() {
    enabled = false;
    OnDisable();
}

std::string Component::getTitle() {
    std::string classname = util::classtitle(typeid(*this).name());
    return classname + (enabled ? "+" : "") + (name != "" && name != classname ? " '" + name + "'" : "");
}

// FIXME: impossibile
template <class T>
T* Component::GetComponent(std::string _name) {
    return entity->GetComponent<T>(_name);
}

template <class T>
T* Component::AddComponent(std::string _name) {
    return entity->AddComponent<T>(_name);
}

std::vector<Component*> Component::GetActiveComponentsInChildren() {
    if (!entity->activeSelf) return vector<Component*>();

    std::vector<Component*> activeComponents;
    activeComponents.clear();

    for (Component* c : entity->Components) {
        if (c->enabled) {
            activeComponents.push_back(c);
        }
    }

    for (Transform* t : entity->transform->children) {
        if (t == nullptr) continue;
        std::vector<Component*> newComponents = t->GetActiveComponentsInChildren();
        activeComponents.insert(activeComponents.end(), newComponents.begin(), newComponents.end());
    }

    return activeComponents;
}

std::vector<Entity*> Component::GetEntitiesInChildren() {
    std::vector<Entity*> entities;
    for (Transform* t : entity->transform->children) {
        if (t == nullptr) continue;
        entities.push_back(t->entity);
        std::vector<Entity*> newEntities = t->GetEntitiesInChildren();
        entities.insert(entities.end(), newEntities.begin(), newEntities.end());
    }

    return entities;
}

// usato solo con i metodi di cycle della base class
void Component::run(Cycle::Stage cycle) {
    switch (cycle) {
        case Cycle::Stage::INIT:
            init();
            break;
        case Cycle::Stage::UPDATE:
            update();
            break;
        case Cycle::Stage::RENDER:
            render();
            break;
        case Cycle::Stage::FIXED:
            fixed();
            break;
        case Cycle::Stage::EXIT:
            exit();
            break;
    }
}

// usato per i metodi custom delle classi derivate (riceve i messages)
void Component::call(string method) {
    // riscritto nelle derived
}

void Component::ReceiveMessage(std::string methodName) {
}

void Component::ReceiveMessage(std::string methodName, Object& parameter) {
    if (methodName == "OnCollisionEnter2D") {
        OnCollisionEnter2D(dynamic_cast<Collision2D&>(parameter));
    } else if (methodName == "OnCollisionExit2D") {
        OnCollisionExit2D(dynamic_cast<Collision2D&>(parameter));
    } else if (methodName == "OnCollisionStay2D") {
        OnCollisionStay2D(dynamic_cast<Collision2D&>(parameter));
    } else if (methodName == "OnTriggerEnter2D") {
        OnTriggerEnter2D(dynamic_cast<Collider2D&>(parameter));
    } else if (methodName == "OnTriggerExit2D") {
        OnTriggerExit2D(dynamic_cast<Collider2D&>(parameter));
    } else if (methodName == "OnTriggerStay2D") {
        OnTriggerStay2D(dynamic_cast<Collider2D&>(parameter));
    }
}

bool Component::isActiveAndEnabled() {
    return enabled && entity->activeSelf && entity->isActiveInHierarchy();
}

void Component::init() {
    Awake();
}

void Component::fixed() {
    currentEnable = isActiveAndEnabled();
    if (!currentEnable) return;

    FixedUpdate();
}

void Component::update() {
    if (!currentEnable) return;

    if (!started) {
        Start();
        started = true;
    }

    Update();
    LateUpdate();

    ResumeCoroutines();
}

void Component::render() {
    if (!currentEnable) return;

    Render();
    OnPostRender();
}

void Component::exit() {
    OnDestroy();
}

// messages
void Component::OnCollisionEnter2D(Collision2D& collision) {}
void Component::OnCollisionExit2D(Collision2D& collision) {}
void Component::OnCollisionStay2D(Collision2D& collision) {}
void Component::OnTriggerEnter2D(Collider2D& collider) {}
void Component::OnTriggerExit2D(Collider2D& collider) {}
void Component::OnTriggerStay2D(Collider2D& collider) {}

// callback overloadabili
void Component::Awake() {}
void Component::Start() {}
void Component::Update() {}
void Component::Render() {}
void Component::FixedUpdate() {}
void Component::LateUpdate() {}
void Component::OnPostRender() {}
void Component::OnEnable() {}
void Component::OnDisable() {}
void Component::OnDestroy() {}

// static
void Component::Sort(vector<Component*>& components) {
    sort(components.begin(), components.end(), [](Component* ca, Component* cb) {
        int sortingLayerA = 0;
        int sortingLayerB = 0;
        int orderInLayerA = 0;
        int orderInLayerB = 0;

        if (dynamic_cast<Renderer*>(ca)) {
            sortingLayerA = ((Renderer*)ca)->sortingLayerID;
            orderInLayerA = ((Renderer*)ca)->sortingOrder;
        }

        if (dynamic_cast<Renderer*>(cb)) {
            sortingLayerB = ((Renderer*)cb)->sortingLayerID;
            orderInLayerB = ((Renderer*)cb)->sortingOrder;
        }

        if (sortingLayerA == sortingLayerB)
            return orderInLayerA < orderInLayerB;
        else
            return sortingLayerA < sortingLayerB;

        return false;
    });
}

}  // namespace se
