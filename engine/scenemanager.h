#pragma once

#include <vector>

#include "scene.h"
#include "gamedata.h"
#include "utility.h"

namespace se {

	//class Cycle;

	class SceneManager {

		public:

			~SceneManager();

			static Scene* activeScene;

			static bool activeSceneSet;

			template<class T>
			static T* LoadScene(string _name = "") { // Adds a scene of class T

				// todo pause e restore dopo
				T* scene = new T();
				scene->name = (_name == "" ? util::classtitle<T>() : _name);

				if (activeSceneSet) {
					delete(activeScene);
					GameData::DestroyAll();
				}
				SetActiveScene(scene);
				return scene;
			}

			static void SetActiveScene(Scene*);
			static void Clear();

			/*template<class T>
			static T* GetSceneByClass() {	// Returns the component of Type type if the game object has one attached, null if it doesn't.
				for(Scene* scene: Scenes) {
					if (dynamic_cast<T*>(scene))
						return dynamic_cast<T*>(scene);
				}
				return nullptr;
			}*/

		protected:

			static vector<Scene*> Scenes;

	};

}
