#include <vector>

#include "scene.h"
#include "maincamera.h"

namespace ShushaoEngine {

	Scene::Scene() {
		root = new Entity("ROOT");
		MainCamera* mainCameraObj = AddEntity<MainCamera>();
		activeCamera = mainCameraObj->camera;
	}

	Scene::~Scene() {
		LOG("Scene Destructor");
		for (Entity* pGO : Entities) {
			delete(pGO);
		}
		Entities.clear();
	}

	Entity* Scene::AddEntity(string _name = "Entity") {
		LOG("Aggiungo una entity vuota: " + _name);
		Entity* entity = new Entity();
		entity->transform->SetParent(root->transform);
		entity->name = _name;

		Entities.push_back(entity);
		return entity;
	}

	void Scene::ScanActiveComponentsInScene() {

		ActiveComponents.clear();
        ActiveComponents = root->GetActiveComponentsInChildren();
	}

	void Scene::run(string cycle) {
		for (Component* c : ActiveComponents) {
			c->run(cycle);
        }
	}

	vector<Entity*> Scene::GetRootEntitys() {

		// TODO: I GAMEOBJECT CON PARENT ROOT

		return Entities;

	}

	void Scene::AddEntity(Entity* pEntity) {
		pEntity->transform->SetParent(root->transform);
		Entities.push_back(pEntity);
	}
}
