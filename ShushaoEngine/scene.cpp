#include <vector>
#include <stdlib.h>

#include "debug.h"
#include "utility.h"
#include "scene.h"
#include "maincamera.h"
#include "gamedata.h"
#include "debuggrid.h"

#include <iostream>

#include <windows.h>

using namespace std;

namespace ShushaoEngine {

	Scene::Scene() {

		name = "Scene";
		root = new Entity("ROOT");
		root->transform->isRoot = true;

		MainCamera* mainCameraObj = AddEntity<MainCamera>();
		activeCamera = mainCameraObj->camera;
		GameData::activeCamera = activeCamera;

		if (Debug::enabled) {
			AddEntity<DebugGrid>("Debug Grid");
		}
	}

	Scene::~Scene() {
		for (Entity* pGO : Entities) {
			delete(pGO);
		}
		Entities.clear();
	}

	Entity* Scene::AddEntity(string _name = "Entity") {

		Entity* entity = new Entity();
		entity->transform->setParent(root->transform);
		entity->name = _name;

		Entities.push_back(entity);
		return entity;
	}

	void Scene::ScanActiveComponentsInScene() {

		ActiveComponents.clear();
        ActiveComponents = root->transform->GetActiveComponentsInChildren();
	}

	void Scene::PrintActiveComponentsInScene() {
		ScanActiveComponentsInScene();
		Logger::setColor(ConsoleColor::DARKCYAN);
		cout << " Scene " << name << " Active Components:" << endl;
		for (Component* component : ActiveComponents) {
			cout << "  - " << component->getTitle() << " (" << component->entity->name << ")" << endl;
		}
		Logger::setColor(ConsoleColor::LIGHTGREY);
	}

	void Scene::PrintActiveRenderersInScene() {
		ScanActiveComponentsInScene();
		Logger::setColor(ConsoleColor::PINK);
		cout << " Scene " << name << " Active Renderers:" << endl;
		for (Component* component : ActiveComponents) {
			if (!dynamic_cast<Renderer*>(component)) continue;
			int layerID = ((Renderer*)component)->sortingLayerID;
			cout << "  - " << "[" << Config::SortingLayers[layerID] << " (" << layerID << ")" << ", " << ((Renderer*)component)->sortingOrder << "] " << component->getTitle()<< " (" << component->entity->name << ")" << endl;
		}
		Logger::setColor(ConsoleColor::LIGHTGREY);
	}

	void Scene::run(string cycle) {
		for (Component* c : ActiveComponents) {
			c->run(cycle);
        }
	}

	void Scene::PrintHierarchy() {
		Logger::setColor(ConsoleColor::GREEN);
		cout << " Scene " << name << "" << endl;
		root->PrintHierarchy(0);
		Logger::setColor(ConsoleColor::LIGHTGREY);
	}

	vector<Entity*> Scene::GetRootEntitys() {

		// TODO: I GAMEOBJECT CON PARENT ROOT

		return Entities;

	}

	void Scene::AddEntity(Entity* pEntity) {
		pEntity->transform->setParent(root->transform);
		Entities.push_back(pEntity);
	}
}
