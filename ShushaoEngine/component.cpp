#include "debug.h"
#include "component.h"
#include "gamedata.h"
#include "cycle.h"


#include "transform.h"
#include "setime.h"

#include <iostream>

#include <algorithm>

using namespace std;

namespace ShushaoEngine {

	Component::Component() {

		name = "Component";
		enabled = true;

		GameData::RegisterComponent(this);

		init();

	}

	Component::~Component() {
		//LOG(INFO, "Component Destructor: " + name + " di " + entity->name);
		OnDestroy();
		exit();
	}

	vector<Component*> Component::GetActiveComponentsInChildren() {

		//cout << endl << " - cerco nei componenti di " << entity->name << endl;

		if (!entity->activeSelf) return vector<Component*>();

		vector<Component*> activeComponents;

		//cout << " - trovati " << entity->Components.size() << endl;

		for (Component* c : entity->Components) {
			//cout << " - controllo " << c->name << " di " << c->entity->name << endl;
			if (c->enabled) {
				//cout << " - attivo " << c->name << " di " << c->entity->name << endl;
				activeComponents.push_back(c);
			}
		}

		//cout << " - ciclo i children di " << entity->name << endl;
		for (Transform* t : entity->transform->children) {
			//cout << " - vado ad aprire i componenti di " << t->entity->name << endl;
            vector<Component*> newComponents = t->GetActiveComponentsInChildren();
            activeComponents.insert(activeComponents.end(), newComponents.begin(), newComponents.end());
        }

        sort(activeComponents.begin(), activeComponents.end(), []( Component* ca, Component* cb ) {

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

			if (sortingLayerA == sortingLayerB) return orderInLayerA < orderInLayerB;
			else return sortingLayerA < sortingLayerB;

			return false;
		});

		return activeComponents;
	}

	// usato solo con i metodi di cycle della base class
	void Component::run(string cycle) {
		if (cycle == Cycle::INIT) init();
		if (cycle == Cycle::UPDATE) update();
		if (cycle == Cycle::RENDER) render();
		if (cycle == Cycle::FIXED) fixed();
		if (cycle == Cycle::EXIT) exit();
	}

	// usato per i metodi custom delle classi derivate (riceve i messages)
	void Component::call(string method) {
		// riscritto nelle derived
	}

	bool Component::isActiveAndEnabled() {
		return enabled && entity->activeSelf && entity->activeInHierarchy;
	}

	void Component::init() {
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
