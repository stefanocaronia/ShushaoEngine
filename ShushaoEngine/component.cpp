#include "component.h"
#include "gamedata.h"

#include <iostream>

#include <algorithm>

using namespace std;

namespace ShushaoEngine {

	Component::Component() {
		cout << "[" << InstanceID << "] Component Constructor" << endl;
		name = "Component";
		enabled = true;

		GameData::RegisterComponent(this);

		init();

	}

	Component::~Component() {
		//OnDestroy();
		exit();
	}

	vector<Component*> Component::GetChildrenActiveComponents() {

		cout << endl << " - cerco nei componenti di " << gameObject->name << endl;

		if (!gameObject->activeSelf) return vector<Component*>();

		vector<Component*> activeComponents;

		cout << " - trovati " << gameObject->Components.size() << endl;

		for (Component* c : gameObject->Components) {
			cout << " - controllo " << c->name << " di " << c->gameObject->name << endl;
			if (c->enabled) {
				cout << " - attivo " << c->name << " di " << c->gameObject->name << endl;
				activeComponents.push_back(c);
			}
		}
		cout << " - ciclo i children di " << gameObject->name << endl;
		for (Transform* t : gameObject->transform->children) {
			cout << " - vado ad aprire i componenti di " << t->gameObject->name << endl;
            vector<Component*> newComponents = t->GetChildrenActiveComponents();
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

	void Component::run(BaseCycle cycle) {

		switch (cycle) {
			case INIT:
				init();
				break;
			case EXIT:
				exit();
				break;
			case UPDATE:
				update();
				break;
			case FIXED_UPDATE:
				fixed();
				break;
			case RENDER:
				render();
				break;
		}
	}

	bool Component::isActiveAndEnabled() {
		return enabled && gameObject->activeSelf && gameObject->activeInHierarchy;
	}


	void Component::init() {
		// to implement in derived classes

		Awake();
	}

	void Component::exit() {
		// to implement in derived classes
	}

	void Component::update() {

		if (!started) {
			Start();
			started = true;
		}
	}

	void Component::render() {

		Update();
		LateUpdate();
	}

	void Component::fixed() {

		FixedUpdate();
	}

	void Component::Awake() {}
	void Component::Start() {}
	void Component::Update() {}
	void Component::FixedUpdate() {}
	void Component::LateUpdate() {}
	void Component::OnPostRender() {}
	void Component::OnEnable() {}
	void Component::OnDisable() {}
	void Component::OnDestroy() {}

}
