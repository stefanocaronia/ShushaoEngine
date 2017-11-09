#pragma once

#include <vector>
#include <string>
#include <typeinfo>

#include "gameobject.h"

using namespace std;

namespace ShushaoEngine {


	class Scene {

		public:
			Scene();
			~Scene();

			string name;
			int BuildIndex;
			bool isLoaded = false;

			GameObject* root;

			Camera* activeCamera;

			vector<GameObject*> GetRootGameObjects();

			void ScanActiveComponentsInScene();

			void run(BaseCycle);

			template<class T>
			T* AddGameObject(string _name = typeid(T).name()) { // Adds a GameObject of class T (Prefab)
				T* obj = new T();
				obj->scene = this;
				obj->name = _name;

				GameObjects.push_back(obj);
				return obj;
			}

			GameObject* AddGameObject(string);

			void AddGameObject(GameObject*);

			vector<GameObject*> GameObjects;
			vector<Component*> ActiveComponents;

		private:
	};

}
