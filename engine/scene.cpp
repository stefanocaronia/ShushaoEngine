#include <vector>
#include <typeinfo>
#include <stdlib.h>
#include <iostream>
#include <windows.h>

#include "scene.h"

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
		entity->transform->SetParent(root->transform);
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
		std::cout << " Scene " << name << " Active Components:" << std::endl;
		for (Component* component : ActiveComponents) {
			std::cout << "  - " << component->getTitle() << " (" << component->entity->name << ")" << std::endl;
		}
		Logger::setColor(ConsoleColor::LIGHTGREY);
	}

	void Scene::PrintActiveRenderersInScene() {
		ScanActiveComponentsInScene();
		Logger::setColor(ConsoleColor::PINK);
		std::cout << " Scene " << name << " Active Renderers:" << std::endl;
		for (Component* component : ActiveComponents) {
			if (!dynamic_cast<Renderer*>(component)) continue;
			int layerID = ((Renderer*)component)->sortingLayerID;
			std::cout << "  - " << "[" << Config::SortingLayers[layerID] << " (" << layerID << ")" << ", " << ((Renderer*)component)->sortingOrder << "] " << component->getTitle()<< " (" << component->entity->name << ")" << std::endl;
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
		std::cout << " Scene " << name << "" << std::endl;
		root->PrintHierarchy(0);
		Logger::setColor(ConsoleColor::LIGHTGREY);
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
