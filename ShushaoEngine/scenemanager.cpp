#include "debug.h"
#include "scenemanager.h"

#include <vector>

namespace ShushaoEngine {

	void SceneManager::Clear() {
		LOG(INFO, "SVUOTO LO SCENEMANAGER");
		for(Scene* s : Scenes) {
			delete(s);
		}
		delete(activeScene);
		Scenes.clear();
	}

	void SceneManager::SetActiveScene(Scene* scene) {
		activeScene = scene;
		GameData::activeScene = scene;
		activeSceneSet = true;
	}

	// init

	bool SceneManager::activeSceneSet;
	vector<Scene*> SceneManager::Scenes;
	Scene* SceneManager::activeScene;

}
