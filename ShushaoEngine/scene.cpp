#include <vector>

#include "debug.h"
#include "scene.h"
#include "maincamera.h"
#include "gamedata.h"
#include "debuggrid.h"

namespace ShushaoEngine {

	Scene::Scene() {

		LOG(INFO, "Constructor di SCENE BASE CLASS");

		root = new Entity("ROOT");
		MainCamera* mainCameraObj = AddEntity<MainCamera>();
		activeCamera = mainCameraObj->camera;
		GameData::activeCamera = activeCamera;

		AddEntity<DebugGrid>("Debug Grid");
		GetEntity<DebugGrid>()->activeSelf = Debug::Enabled;
	}

	Scene::~Scene() {
		LOG(INFO, "Scene Destructor");
		for (Entity* pGO : Entities) {
			delete(pGO);
		}
		Entities.clear();
	}

	Entity* Scene::AddEntity(string _name = "Entity") {
		LOG(INFO, "Aggiungo una entity vuota: " + _name);
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

	void Scene::PrintHierarchy() {
		root->PrintHierarchy(0);
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
