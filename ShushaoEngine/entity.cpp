#include "entity.h"
#include "transform.h"
#include "spriterenderer.h"

#include <iostream>
#include <iostream>
#include "debug.h"

using namespace std;

namespace ShushaoEngine {

	Entity::Entity() {

		cout << "[" << InstanceID << "] Entity Constructor" << endl;

		name = "Entity";
		activeSelf = true;
		isStatic = false;

		vector<Component*> Components;

		transform = AddComponent<Transform>();
	}

	Entity::~Entity() {

		LOG("Entity Destructor: " + name);

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

		cout << "[" << InstanceID << "] Entity Constructor" << endl;

		transform = AddComponent<Transform>();
	}

	vector<Component*> Entity::GetActiveComponentsInChildren() {
		return transform->GetActiveComponentsInChildren();
	}

	void Entity::run(string cycle) {
		//cout << "Entity " << name << ": run " << to_string(cycle) << endl;
		if (!GetActiveState()) {
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

	bool Entity::GetActiveState() {
		if (!activeSelf) return false;

		/*Transform* p = transform->GetParent();
		while (p != nullptr) {
			if (!p->entity->activeSelf) {
				activeInHierarchy = false;
				return false;
			} else {
				p = p->GetParent();
			}
		}*/

		return true;
	}


}
