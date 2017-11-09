#pragma once

#include <vector>
#include <string>
#include <typeinfo>

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

			void run(string);

			template<class T>
			T* AddEntity(string _name = typeid(T).name()) { // Adds a Entity of class T (Prefab)
				T* entity = new T();
				entity->scene = this;
				entity->name = _name;

				Entities.push_back(entity);
				return entity;
			}

			Entity* AddEntity(string);

			void AddEntity(Entity*);

			vector<Entity*> Entities;
			vector<Component*> ActiveComponents;

		private:
	};

}
