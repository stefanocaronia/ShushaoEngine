#pragma once

#include <vector>

#include "scene.h"
#include "gamedata.h"

namespace ShushaoEngine {

	class GLGame;

	class SceneManager {

		private:

			SceneManager() {}
			~SceneManager();
			SceneManager(const SceneManager&);
			SceneManager& operator=(const SceneManager&);

		public:

			static SceneManager& GetInstance(GLGame* pGame) {
				static SceneManager instance;
				instance.game = pGame;
				return instance;
			}

			GLGame* game;

			Scene* activeScene;

			template<class T>
			T* LoadScene() { // Adds a scene of class T

				// todo pause e restore dopo
				T* scene = new T();
				if (activeScene != nullptr) {
					delete(activeScene);
					GameData::DestroyAll();
				}
				SetActiveScene(scene);
				return scene;
			}

			void SetActiveScene(Scene* scene) {
				activeScene = scene;
				GameData::activeScene = scene;
			}

			/*template<class T>
			T* GetSceneByClass() {	// Returns the component of Type type if the game object has one attached, null if it doesn't.
				for(Scene* scene: Scenes) {
					if (dynamic_cast<T*>(scene))
						return dynamic_cast<T*>(scene);
				}
				return nullptr;
			}*/

		protected:

			vector<Scene*> Scenes;

		private:
	};

}
