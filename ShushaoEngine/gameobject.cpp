#include "gameobject.h"
#include "transform.h"
#include "spriterenderer.h"

#include <iostream>
#include <algorithm>

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

	vector<Component*> GameObject::GetChildrenActiveComponents() {
		if (!activeSelf) return vector<Component*>();

		vector<Component*> activeComponents;

		for (Component* c : Components) {
			if (c->enabled) {
				activeComponents.push_back(c);
			}
		}

		for (Transform* t : *transform) {
            vector<Component*> newComponents = t->gameObject->GetChildrenActiveComponents();
            activeComponents.insert(activeComponents.end(), newComponents.begin(), newComponents.end());
        }

        sort(activeComponents.begin(), activeComponents.end(), []( Component* ca, Component* cb ) {

			int sortingLayerA, sortingLayerB, orderInLayerA, orderInLayerB;

			sortingLayerA = ca->sortingLayerID;
			orderInLayerA = ca->sortingOrder;
			sortingLayerB = cb->sortingLayerID;
			orderInLayerB = cb->sortingOrder;

			if (sortingLayerA == sortingLayerB) return orderInLayerA < orderInLayerB;
			else return sortingLayerA < sortingLayerB;

			return false;
		});

		return activeComponents;
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
