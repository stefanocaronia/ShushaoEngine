#pragma once

#include <vector>
#include <string>
#include <typeinfo>

#include "debug.h"
#include "camera.h"
#include "entity.h"
#include "utility.h"

using namespace std;

namespace ShushaoEngine {

	class Scene {

		public:
			Scene();
			~Scene();

			string name;
			int BuildIndex;
			bool isLoaded = false;

			Entity* root;

			Camera* activeCamera;

			vector<Entity*> GetRootEntitys();

			void ScanActiveComponentsInScene();
			void PrintActiveComponentsInScene();
			void PrintActiveRenderersInScene();
			void PrintHierarchy();

			void run(string);

			template<class T>
			T* AddEntity(string _name = "") { // Adds a Entity of class T (Prefab)

				T* entity = new T();
				entity->name = (_name == "" ? util::classtitle<T>() : _name);
				entity->scene = this;
				entity->transform->setParent(root->transform);

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

			Entity* AddEntity(string);

			void AddEntity(Entity*);

			vector<Entity*> Entities;
			vector<Component*> ActiveComponents;

		private:
	};

}
