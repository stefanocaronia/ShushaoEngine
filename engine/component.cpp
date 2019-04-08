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

using namespace std;
using ComponentSet = std::multiset<Component*, Component::Compare>;

Component::Component() {
    name = getTitle();
    enabled = true;
    GameData::RegisterComponent(this);
}

Component::~Component() {
    Debug::Log << "Component Destructor: " << name << " di " << entity->name << endl;
    exit();
}

void Component::Copy(Component* other) {
    if (other == nullptr) return;
    Object::Copy(other);

    // NB: non copio l'entity e non copio il transform
    sortingLayerID = other->sortingLayerID;
    sortingOrder = other->sortingOrder;
    tag = other->tag;
    currentEnable = other->currentEnable;
    started = other->started;
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

ComponentSet Component::GetActiveComponentsInChildren() {
    if (!entity->active) return ComponentSet();

    ComponentSet activeComponents;

    for (Component* c : entity->Components) {
        if (c->enabled) {
            activeComponents.insert(c);
        }
    }

    for (Transform* tr : entity->transform->children) {
        if (tr == nullptr) continue;
        ComponentSet newComponents = tr->GetActiveComponentsInChildren();
        activeComponents.insert(newComponents.begin(), newComponents.end());
    }

    return activeComponents;
}

std::set<Entity*> Component::GetEntitiesInChildren() {
    std::set<Entity*> entities;
    for (Transform* t : entity->transform->children) {
        if (t == nullptr) continue;
        entities.insert(t->entity);
        std::set<Entity*> newEntities = t->GetEntitiesInChildren();
        entities.insert(newEntities.begin(), newEntities.end());
    }

    return entities;
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
    return enabled && entity->active && entity->isActiveInHierarchy();
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

/*
    Custom compare function used to sort the multiset
*/
bool Component::Compare::operator()(Component* A, Component* B) const {
    if (A->sortingLayerID == B->sortingLayerID)
        return A->sortingOrder < B->sortingOrder;
    else
        return A->sortingLayerID < B->sortingLayerID;
}

}  // namespace se
