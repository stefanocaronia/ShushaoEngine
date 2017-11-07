#include "scenemanager.h"

#include <vector>

namespace ShushaoEngine {

	/*void SceneManager::AddScene(Scene* pScene) {
		pScene->BuildIndex = ++buildCounter;
		Scenes.push_back(pScene);
	}*/

	/*Scene* SceneManager::GetSceneByName(string name) {

        if (Scenes.size() == 0) return nullptr;

        for (Scene* pScene: Scenes) {
            if (pScene->name == name) return pScene;
        }

        // return &Type();
        return nullptr;
	}*/

	SceneManager::~SceneManager() {
		for(Scene* s : Scenes) {
			delete(s);
		}
		Scenes.clear();
	}
}
