#include "entity.h"
#include "scene.h"
#include "transform.h"

namespace se {

Entity::Entity() {
    name = "Entity";
    active = true;
    isStatic = false;

    transform = AddComponent<Transform>();
}

void Entity::init() {
    if (isInitialized) return;
    if (!addedToScene) {
        scene->Entities.insert(this);
    }
    Init();
    isInitialized = true;
}

Entity::~Entity() {
    Debug::Log << "Entity Destructor: " << name << endl;

    // distruggo tutti i components
    for (Component* pCO : Components) {
        delete(pCO);
    }
    Components.clear();
}

Entity::Entity(string _name) {
    name = _name;
    active = true;
    isStatic = false;

    transform = AddComponent<Transform>();
}

void Entity::Copy(Entity* other) {
    if (other == nullptr) return;
    Object::Copy(other);

    canvas = other->canvas;
    scene = other->scene;
    layer = other->layer;
    tag = other->tag;
    tags = other->tags;
    activeInHierarchy = other->activeInHierarchy;
    active = other->active;
    isStatic = other->isStatic;

    auto c = Components.begin();
    auto oc = other->Components.begin();
    for (; c != Components.end(); c++, oc++) {
        (*c)->Copy(*oc);
    }
}

Entity* Entity::AddChild(string _name = "Entity") {
    Entity* entity = new Entity();
    entity->transform->SetParent(transform);
    entity->scene = scene;
    entity->name = _name;
    if (entity->scene != nullptr) {
        scene->Entities.insert(entity);
        entity->addedToScene = true;
        entity->init();
    }
    return entity;
}

std::multiset<Component*, Component::Compare> Entity::GetActiveComponentsInChildren() {
    return transform->GetActiveComponentsInChildren();
}

void Entity::BroadcastMessage(std::string methodName) {
    /*		if (!isActiveInHierarchy())	return;

        for (Component* c : Components) {
            if (c->enabled)
				c->ReceiveMessage(methodName);
        }

        for (Transform* t : transform->children)
            t->entity->SendMessage(methodName);
*/
}

void Entity::SendMessage(std::string methodName, Object& parameter) {
    if (!isActiveInHierarchy()) return;

    for (Component* c : Components) {
        if (c->enabled) c->ReceiveMessage(methodName, parameter);
    }
}

void Entity::PrintHierarchy(int level) {
    Logger::setColor(ConsoleColor::DARKGREEN);

    for (int i = 0; i < level; i++) cout << "   ";
    cout << " " << (char)192 << (char)196;
    cout << " " << name << (active ? "+" : "");

    for (Component* c : Components) cout << " [" << c->index << ". " << c->getTitle() << "]";

    cout << endl;

    ++level;
    for (Transform* t : transform->children) {
        t->entity->PrintHierarchy(level);
    }

    Logger::setColor(ConsoleColor::WHITE);
}

bool Entity::isActiveInHierarchy() {
    if (!active) return false;

    /*Transform* p = transform->getParent();
		while (p != nullptr) {
			if (!p->entity->active)
				return activeInHierarchy = false;
			p = p->getParent();
		}*/

    return true;
}

void Entity::SetParent(Entity* other) {
    transform->SetParent(other->transform);
    canvas = other->canvas;
}

unsigned int Entity::GetNextIndex() {
    if (Components.size() > 0) {
        auto max = max_element(Components.begin(), Components.end(), [](const Component* a, const Component* b) {
            return a->index < b->index;
        });

        return (*max)->index + 1;
    }
    return 1;
}

}  // namespace se
