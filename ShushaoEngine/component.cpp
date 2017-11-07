#include "component.h"
#include "gamedata.h"

#include <iostream>

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

	void Component::run(BaseCycle cycle) {

		switch (cycle) {
			case INIT:
				init();
				break;
			case EXIT:
				exit();
				break;
			case UPDATE:
				updateCycle();
				break;
			case FIXED_UPDATE:
				fixedUpdateCycle();
				break;
			case RENDER:
				renderCycle();
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

	void Component::updateCycle() {

		if (!started) {
			Start();
			started = true;
		}
	}

	void Component::renderCycle() {

		Update();
		LateUpdate();
	}

	void Component::fixedUpdateCycle() {

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
