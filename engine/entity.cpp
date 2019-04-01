#include "entity.h"
#include "transform.h"
#include "scene.h"

namespace se {

	Entity::Entity() {

		name = "Entity";
		activeSelf = true;
		isStatic = false;

		transform = AddComponent<Transform>();
	}

	void Entity::init() {
		if (isInitialized) return;
		if (!addedToScene) {
			scene->Entities.push_back(this);
		}
		Init();
		isInitialized = true;
	}

	Entity::~Entity() {

		Debug::Log << "Entity Destructor: " << name << endl;

		// distruggo tutti i components
		for(Component* pCO : Components) {
			delete(pCO);
		}
		Components.clear();
	}

	Entity::Entity(string _name) {
		name = _name;
		activeSelf = true;
		isStatic = false;

		transform = AddComponent<Transform>();
	}

	Entity* Entity::AddChild(string _name = "Entity") {
		Entity* entity = new Entity();
		entity->transform->SetParent(transform);
		entity->scene = scene;
		entity->name = _name;
		if (entity->scene != nullptr) {
			scene->Entities.push_back(entity);
			entity->addedToScene = true;
			entity->init();
		}
		return entity;
	}

	vector<Component*> Entity::GetActiveComponentsInChildren() {
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
		if (!isActiveInHierarchy())	return;

        for (Component* c : Components) {
            if (c->enabled)	c->ReceiveMessage(methodName, parameter);
        }

	}

	void Entity::run(Cycle::Stage cycle) {
		if (!isActiveInHierarchy()) {
			return;
		}

        for (Component* c : Components) {
            if (c->enabled) {
				c->run(cycle);
            }
        }

        for (Transform* t : transform->children) {
            t->entity->run(cycle);
        }
	}

	void Entity::PrintHierarchy(int level) {

		Logger::setColor(ConsoleColor::DARKGREEN);

		for (int i = 0; i < level; i++) cout << "   ";
		cout << " " << (char)192 << (char)196;
		cout << " " << name << (activeSelf ? "+": "");

        for (Component* c : Components) cout << " [" << c->getTitle() << "]";

        cout << endl;

        ++level;
        for (Transform* t : transform->children) {
            t->entity->PrintHierarchy(level);
        }

        Logger::setColor(ConsoleColor::WHITE);
	}

	bool Entity::isActiveInHierarchy() {
		if (!activeSelf) return false;

		/*Transform* p = transform->getParent();
		while (p != nullptr) {
			if (!p->entity->activeSelf)
				return activeInHierarchy = false;
			p = p->getParent();
		}*/

		return true;
	}

	void Entity::setParent(Entity* other) {
		transform->SetParent(other->transform);
		canvas = other->canvas;
	}


}
