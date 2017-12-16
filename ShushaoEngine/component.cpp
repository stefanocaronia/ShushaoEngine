#include <algorithm>

#include "component.h"
#include "debug.h"
#include "utility.h"
#include "cycle.h"
#include "setime.h"
#include "transform.h"
#include "renderer.h"
#include "gamedata.h"
#include "collision2d.h"

namespace ShushaoEngine {

	Component::Component() {

		name = "Component";
		enabled = true;

		GameData::RegisterComponent(this);

		init();

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
		return classname + (enabled ? "+": "") + (name != "" && name != classname ? " '" + name +"'": "");
	}

	std::vector<Component*> Component::GetActiveComponentsInChildren() {

		if (!entity->activeSelf) return vector<Component*>();

		std::vector<Component*> activeComponents;

		for (Component* c : entity->Components) {
			if (c->enabled) {
				activeComponents.push_back(c);
			}
		}

		for (Transform* t : entity->transform->children) {
            std::vector<Component*> newComponents = t->GetActiveComponentsInChildren();
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

			if (sortingLayerA == sortingLayerB)
				return orderInLayerA < orderInLayerB;
			else
				return sortingLayerA < sortingLayerB;

			return false;
		});

		return activeComponents;
	}

	// usato solo con i metodi di cycle della base class
	void Component::run(string cycle) {
		if (cycle == Cycle::INIT) init();
		else if (cycle == Cycle::UPDATE) update();
		else if (cycle == Cycle::RENDER) render();
		else if (cycle == Cycle::FIXED) fixed();
		else if (cycle == Cycle::EXIT) exit();
	}

	// usato per i metodi custom delle classi derivate (riceve i messages)
	void Component::call(string method) {
		// riscritto nelle derived
	}

	void Component::ReceiveMessage(std::string methodName) {

	}

	void Component::ReceiveMessage(std::string methodName, Object* parameter) {
        if (methodName == "OnCollisionEnter2D") {
			OnCollisionEnter2D(dynamic_cast<Collision2D*>(parameter));
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
	void Component::OnCollisionEnter2D(Collision2D* collision) {}

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

}
