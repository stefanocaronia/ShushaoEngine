#pragma once

#include <vector>

#include "scene.h"
#include "gamedata.h"

namespace ShushaoEngine {

	//class Cycle;

	class SceneManager {

		public:

			//static Cycle* game;

			static Scene* activeScene;

			template<class T>
			static T& LoadScene() { // Adds a scene of class T

				// todo pause e restore dopo
				T* scene = new T();
				if (activeScene != nullptr) {
					delete(activeScene);
					GameData::DestroyAll();
				}
				SetActiveScene(*scene);
				return *scene;
			}

			static void SetActiveScene(Scene& scene) {
				activeScene = &scene;
				GameData::activeScene = &scene;
			}

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
