#include <vector>

#include "scene.h"
#include "maincamera.h"

namespace ShushaoEngine {

	Scene::Scene() {
		AddGameObject("ROOT"); // add root gameObject
		GameObject* cameraGameObject = AddGameObject<MainCamera>();
		activeCamera = cameraGameObject->GetComponent<Camera>();
	}

	Scene::~Scene() {
		for (GameObject* pGO : GameObjects) {
			delete(pGO);
		}
		GameObjects.clear();
	}

	GameObject* Scene::AddGameObject(string _name = "GameObject") {
		GameObject* obj = new GameObject();
		if (root == nullptr) {
			root = obj;
			obj->name = "ROOT";
		} else {
			obj->transform->SetParent(root->transform);
			obj->name = _name;
		}
		return obj;
	}

	void Scene::ScanActiveComponentsInScene() {
		if (root == nullptr) return;

		ActiveComponents.clear();
        ActiveComponents = root->GetChildrenActiveComponents();
	}

	void Scene::run(BaseCycle cycle) {
		for (Component* c : ActiveComponents) {
			c->run(cycle);
        }
	}

	vector<GameObject*> Scene::GetRootGameObjects() {

		// TODO: I GAMEOBJECT CON PARENT ROOT

		return GameObjects;

	}

	void Scene::AddGameObject(GameObject* pGameObject) {
		if (root == nullptr) return;
		pGameObject->transform->SetParent(root->transform);
		GameObjects.push_back(pGameObject);
	}
}
