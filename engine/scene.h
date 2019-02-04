#pragma once

#include <vector>
#include <string>

#include "utility.h"
#include "entity.h"

namespace ShushaoEngine {

	class Component;
	class Camera;

	class Scene {

		public:
			Scene();
			~Scene();

			std::string name;
			int BuildIndex;
			bool isLoaded = false;

			Entity* root;

			Camera* activeCamera;

			std::vector<Entity*> GetRootEntitys();

			void ScanActiveComponentsInScene();
			void PrintActiveComponentsInScene();
			void PrintActiveRenderersInScene();
			void PrintHierarchy();

			void run(std::string);

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
			T* GetEntity() {	// Returns the component of Type type if the game object has one attached, null if it doesn't.
				for(Entity* entity: Entities) {
					if (dynamic_cast<T*>(entity))
						return dynamic_cast<T*>(entity);
				}
				return nullptr;
			}

			Entity* AddEntity(std::string);

			void AddEntity(Entity*);

			std::vector<Entity*> Entities;
			std::vector<Component*> ActiveComponents;

		private:
	};

}
