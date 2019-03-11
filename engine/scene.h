#pragma once

#include <vector>
#include <string>

#include "utility.h"
#include "entity.h"
#include "debug.h"
#include "transform.h"
#include "entity.h"
#include "utility.h"
#include "maincamera.h"
#include "gamedata.h"
#include "debuggrid.h"
#include "renderer.h"
#include "light.h"

namespace se {

	class Component;
	class Camera;

	class Scene {

		public:
			Scene();
			~Scene();

			std::string name = "";
			int BuildIndex;
			bool isLoaded = false;

			Entity* root;
			Camera* activeCamera;

			std::vector<Entity*> Entities;
			std::vector<Component*> ActiveComponents;
			std::vector<Light*> ActiveLights;
			//std::vector<Renderer*> ActiveRenderers;
			std::vector<Renderer*> ActiveOverlayRenderers;

			void run(std::string);
			void overlayRender();

			std::vector<Entity*> GetRootEntitys();

			// scan
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

				Entities.push_back(entity);
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
