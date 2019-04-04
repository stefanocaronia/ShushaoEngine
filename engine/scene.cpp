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
		entity->scene = this;
		entity->name = _name;

		Entities.insert(entity);
		entity->addedToScene = true;
		entity->init();
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
		ActiveOverlayRenderers.clear();

		// ottengo i component attivi
        ActiveComponents = root->transform->GetActiveComponentsInChildren();

		for (Component* component : ActiveComponents) {
			Renderer* renderer = dynamic_cast<Renderer*>(component);
			if (renderer != nullptr && renderer->overlay)
				ActiveOverlayRenderers.insert(component);
		}

		// ordino tutti gli oggetti in ordine di rendering
		// Component::Sort(ActiveComponents);
		// Component::Sort(ActiveOverlayRenderers);

		componentsScanned = true;
	}

	void Scene::InitEntities() {
		// ottengo tutte le entities anche child
        set<Entity*> entities = root->transform->GetEntitiesInChildren();

		for (auto& entity: entities) {
			if (!entity->isInitialized) {
				entity->init();
			}
			if (!entity->addedToScene) {
				Entities.insert(entity);
				entity->addedToScene = true;
			}
		}
	}

	void Scene::ScanActiveLights() {
		ScanActiveComponents();
		ActiveLights.clear();
		for (Component* component : ActiveComponents) {
			if (dynamic_cast<Light*>(component)) {
				ActiveLights.insert((Light*)component);
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
			std::cout << "  - " << "[" << Config::SortingLayers[layerID] << " (" << layerID << ")" << ", " << component->sortingOrder << "] " << component->getTitle()<< " (" << component->entity->name << ")" << std::endl;
		}
		std::cout << " Scene " << name << " Active Overlay Renderers:" << std::endl;
		for (Component* component : ActiveOverlayRenderers) {
			if (!dynamic_cast<Renderer*>(component)) continue;
			int layerID = ((Renderer*)component)->sortingLayerID;
			std::cout << "  - " << "[" << Config::SortingLayers[layerID] << " (" << layerID << ")" << ", " << component->sortingOrder << "] " << component->getTitle()<< " (" << component->entity->name << ")" << std::endl;
		}
		Logger::setColor(ConsoleColor::LIGHTGREY);
	}

	void Scene::run(Cycle::Stage cycle) {
		for (Component* component : ActiveComponents) {
			if (cycle == Cycle::Stage::RENDER) {
				Renderer* renderer = dynamic_cast<Renderer*>(component);
				if (renderer != nullptr && renderer->overlay) // non eseguo il rendering degli overlay in questo ciclo
					continue;
			}
			component->run(cycle);
        }
	}

	void Scene::renderOverlay() {
		for (Component* component : ActiveOverlayRenderers) {
			component->run(Cycle::Stage::RENDER);
        }
	}

	void Scene::PrintHierarchy() {
		if (!Debug::enabled) return;
		Logger::setColor(ConsoleColor::GREEN);
		std::cout << " Scene " << name << "" << std::endl;
		root->PrintHierarchy(0);
		Logger::setColor(ConsoleColor::LIGHTGREY);
	}

	set<Entity*> Scene::GetRootEntitys() {
		// TODO: I GAMEOBJECT CON PARENT ROOT
		return Entities;
	}

	Entity* Scene::AddEntity(Entity* pEntity) {
		pEntity->transform->SetParent(root->transform);
		Entities.insert(pEntity);
		return pEntity;
	}
}
