#include "scenemanager.h"

#include <vector>

namespace ShushaoEngine {

	void SceneManager::Clear() {
		for(Scene* s : Scenes) {
			delete(s);
		}
		Scenes.clear();
	}


	// init

	vector<Scene*> SceneManager::Scenes;
	Scene* SceneManager::activeScene;

}
