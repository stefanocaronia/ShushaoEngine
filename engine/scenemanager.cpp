#include <vector>

#include "debug.h"
#include "scenemanager.h"

namespace se {

	void SceneManager::Clear() {
		for(Scene* s : Scenes) {
			delete(s);
		}
		delete(activeScene);
		Scenes.clear();
	}

	void SceneManager::Setscene(Scene* scene_) {
		activeScene = scene_;
		GameData::scene = scene_;
		sceneSet = true;
	}

	// init

	bool SceneManager::sceneSet = false;
	vector<Scene*> SceneManager::Scenes;
	Scene* SceneManager::activeScene = nullptr;

}
