#include <vector>
#include <typeinfo>
#include <stdlib.h>
#include <iostream>
#include <windows.h>

#include "scene.h"
#include "cycle.h"

namespace se {

	using namespace std;

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
		delete(root);
		Entities.clear();
	}

	Entity* Scene::AddEntity(string _name = "Entity") {

		Entity* entity = new Entity();
		entity->transform->SetParent(root->transform);
		entity->name = _name;

		Entities.push_back(entity);
		return entity;
	}

	Entity* Scene::GetEntity(std::string name_) {
		for(Entity* entity: Entities) {
			if (entity->name == name_)
				return entity;
		}
		return nullptr;
	}

	void Scene::ScanActiveComponents() {
		if (componentsScanned) return;
		ActiveComponents.clear();
        ActiveComponents = root->transform->GetActiveComponentsInChildren();
		SortActiveComponents();
		componentsScanned = true;
	}

	void Scene::SortActiveComponents() {
		sort(ActiveComponents.begin(), ActiveComponents.end(), []( Component* ca, Component* cb ) {

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
	}

	void Scene::ScanActiveLights() {
		ScanActiveComponents();
		ActiveLights.clear();
		for (Component* component : ActiveComponents) {
			if (dynamic_cast<Light*>(component)) {
				ActiveLights.push_back((Light*)component);
			}
		}
	}

	void Scene::ScanActiveRenderers() {
		ScanActiveComponents();
		for (Component* component : ActiveComponents) {
			if (dynamic_cast<Renderer*>(component) && ((Renderer*)component)->overlay) {
				ActiveOverlayRenderers.push_back((Renderer*)component);
			}
		}
	}

	void Scene::PrintActiveComponentsInScene() {
		ScanActiveComponents();
		if (!Debug::enabled) return;
		Logger::setColor(ConsoleColor::DARKCYAN);
		std::cout << " Scene " << name << " Active Components:" << std::endl;
		for (Component* component : ActiveComponents) {
			std::cout << "  - " << component->getTitle() << " (" << component->entity->name << ")" << std::endl;
		}
		Logger::setColor(ConsoleColor::LIGHTGREY);
	}

	void Scene::PrintActiveLightsInScene() {
		ScanActiveLights();
		if (!Debug::enabled) return;
		Logger::setColor(ConsoleColor::PINK);
		std::cout << " Scene " << name << " Active Lights:" << std::endl;
		for (Light* light : ActiveLights) {
			std::cout << "  - " << light->GetTypeDesc() << " light " << light->getTitle() << " (" << light->entity->name << ")" << std::endl;
		}
		Logger::setColor(ConsoleColor::LIGHTGREY);
	}

	void Scene::PrintActiveRenderersInScene() {
		ScanActiveComponents();
		if (!Debug::enabled) return;
		Logger::setColor(ConsoleColor::DARKPURPLE);
		std::cout << " Scene " << name << " Active Renderers:" << std::endl;
		for (Component* component : ActiveComponents) {
			if (!dynamic_cast<Renderer*>(component)) continue;
			int layerID = ((Renderer*)component)->sortingLayerID;
			std::cout << "  - " << "[" << Config::SortingLayers[layerID] << " (" << layerID << ")" << ", " << ((Renderer*)component)->sortingOrder << "] " << component->getTitle()<< " (" << component->entity->name << ")" << std::endl;
		}
		Logger::setColor(ConsoleColor::LIGHTGREY);
	}

	void Scene::run(string cycle) {
		for (Component* component : ActiveComponents) {
			// non renderizzo i renderer overlay
			if (cycle == Cycle::RENDER && dynamic_cast<Renderer*>(component) && ((Renderer*)component)->overlay) {
				return;
			} else {
				component->run(cycle);
			}
        }
	}

	void Scene::overlayRender() {
		for (Renderer* renderer : ActiveOverlayRenderers) {
			renderer->run(Cycle::RENDER);
        }
	}

	void Scene::PrintHierarchy() {
		if (!Debug::enabled) return;
		Logger::setColor(ConsoleColor::GREEN);
		std::cout << " Scene " << name << "" << std::endl;
		root->PrintHierarchy(0);
		Logger::setColor(ConsoleColor::LIGHTGREY);
	}

	vector<Entity*> Scene::GetRootEntitys() {
		// TODO: I GAMEOBJECT CON PARENT ROOT
		return Entities;
	}

	Entity* Scene::AddEntity(Entity* pEntity) {
		pEntity->transform->SetParent(root->transform);
		Entities.push_back(pEntity);
		return pEntity;
	}
}
