#pragma once

#include <set>
#include <string>

#include "utility.h"
#include "entity.h"
#include "debug.h"
#include "component.h"
#include "transform.h"
#include "entity.h"
#include "utility.h"
#include "maincamera.h"
#include "gamedata.h"
#include "debuggrid.h"
#include "renderer.h"
#include "light.h"
#include "cycle.h"

namespace se {

	// class Component;
	class Camera;

	class Scene {

		public:
			Scene();
			~Scene();

			std::string name = "";
			int BuildIndex;
			bool isLoaded = false;

			Entity* root = nullptr;
			Camera* activeCamera = nullptr;

			std::set<Entity*> Entities;
			std::multiset<Component*, Component::Compare> ActiveComponents;
			std::set<Light*> ActiveLights;
			std::multiset<Component*, Component::Compare> ActiveOverlayRenderers;

			void run(Cycle::Stage stage);
			void renderOverlay();

			std::set<Entity*> GetRootEntitys();

			// scan
			void InitEntities();
			void ScanActiveComponents();
			void SortActiveComponents();
			void ScanActiveLights();
			void ScanActiveRenderers();
			bool componentsScanned = false;

			// debug
			void PrintActiveComponentsInScene();
			void PrintActiveRenderersInScene();
			void PrintActiveLightsInScene();
			void PrintHierarchy();

			Entity* AddEntity(Entity*);
			Entity* AddEntity(std::string);
			Entity* GetEntity(std::string);

			template<class T>
			T* AddEntity(std::string _name = "") { // Adds a Entity of class T (Prefab)

				T* entity = new T();
				entity->name = (_name == "" ? util::classtitle<T>() : _name);
				entity->scene = this;
				entity->transform->SetParent(root->transform);

				Entities.insert(entity);
				entity->addedToScene = true;
				entity->init();
				return entity;
			}

			template<class T>
			T* GetEntity() {
				for(Entity* entity: Entities) {
					if (dynamic_cast<T*>(entity))
						return dynamic_cast<T*>(entity);
				}
				return nullptr;
			}

		private:
	};

}
