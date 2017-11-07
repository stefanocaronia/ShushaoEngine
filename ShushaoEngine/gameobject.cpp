#include "gameobject.h"
#include "transform.h"
#include "spriterenderer.h"

#include <iostream>

using namespace std;

namespace ShushaoEngine {

	GameObject::GameObject() {

		cout << "[" << InstanceID << "] GameObject Constructor" << endl;

		name = "GameObject";
		activeSelf = true;
		isStatic = false;

		transform = AddComponent<Transform>();
	}

	GameObject::~GameObject() {

		// distruggo tutti i components
		for(Component* pCO : Components) {
			delete(pCO);
		}
		Components.clear();
	}

	GameObject::GameObject(string _name) {
		name = _name;
		activeSelf = true;
		isStatic = false;

		cout << "[" << InstanceID << "] GameObject Constructor" << endl;

		transform = AddComponent<Transform>();
	}

	void GameObject::run(BaseCycle cycle) {
		//cout << "GameObject " << name << ": run " << to_string(cycle) << endl;
		if (!GetActiveState()) {
			//cout << "GameObject " << name << ": non attivo " << endl;
			return;
		}

        for (Component* c : Components) {
            if (c->enabled) {
				//cout << "Component " << c->name << ": run " << to_string(cycle) << endl;
				c->run(cycle);
            }
        }

        for (Transform* t : *transform) {
			//cout << "In trasnform di " <<  t->gameObject->name << endl;
            t->gameObject->run(cycle);
        }

	}

	bool GameObject::GetActiveState() {
		if (!activeSelf) return false;

		/*Transform* p = transform->GetParent();
		while (p != nullptr) {
			if (!p->gameObject->activeSelf) {
				activeInHierarchy = false;
				return false;
			} else {
				p = p->GetParent();
			}
		}*/

		return true;
	}


}
