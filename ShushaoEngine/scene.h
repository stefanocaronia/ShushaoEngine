#pragma once

#include <vector>
#include <string>
#include <typeinfo>

#include "utility.h"
#include "debug.h"
#include "entity.h"

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
			void PrintHierarchy();

			void run(string);

			template<class T>
			T* AddEntity(string _name = typeid(T).name()) { // Adds a Entity of class T (Prefab)

				LOG(INFO, "Aggiungo un entity di classe " + Utility::toString(typeid(T).name()));
				T* entity = new T();
				entity->scene = this;
				entity->name = _name;
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

			Entity* AddEntity(string);

			void AddEntity(Entity*);

			vector<Entity*> Entities;
			vector<Component*> ActiveComponents;

		private:
	};

}
