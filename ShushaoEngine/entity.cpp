#include "entity.h"
#include "transform.h"
#include "spriterenderer.h"

#include <iostream>
#include "debug.h"

using namespace std;

namespace ShushaoEngine {

	Entity::Entity() {

		name = "Entity";
		activeSelf = true;
		isStatic = false;

		//vector<Component*> Components;

		transform = AddComponent<Transform>();
	}

	Entity::~Entity() {

		LOG(INFO, "Entity Destructor: " + name);

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

	vector<Component*> Entity::GetActiveComponentsInChildren() {
		return transform->GetActiveComponentsInChildren();
	}

	void Entity::run(string cycle) {
		//cout << "Entity " << name << ": run " << to_string(cycle) << endl;
		if (!isActiveInHierarchy()) {
			//cout << "Entity " << name << ": non attivo " << endl;
			return;
		}

        for (Component* c : Components) {
            if (c->enabled) {
				//cout << "Component " << c->name << ": run " << to_string(cycle) << endl;
				c->run(cycle);
            }
        }

        for (Transform* t : transform->children) {
			//cout << "In trasnform di " <<  t->entity->name << endl;
            t->entity->run(cycle);
        }

	}

	void Entity::PrintHierarchy(int level) {

		Debug::SetColor(DARKGREEN);

		for (int i = 0; i < level; i++) cout << "   ";

		cout << " " << (char)192 << (char)196;

		cout << " " << name << (activeSelf ? "+": "");

        for (Component* c : Components) cout << " [" << c->getTitle() << "]";

        cout << endl;

        ++level;
        for (Transform* t : transform->children) {
            t->entity->PrintHierarchy(level);
        }

        Debug::SetColor(WHITE);

	}

	bool Entity::isActiveInHierarchy() {
		if (!activeSelf) return false;

		/*Transform* p = transform->GetParent();
		while (p != nullptr) {
			if (!p->entity->activeSelf)
				return activeInHierarchy = false;
			p = p->GetParent();
		}*/

		return true;
	}

	void Entity::setParent(Entity* other) {
		transform->setParent(other->transform);
	}


}
