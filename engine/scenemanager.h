#pragma once

#include "pch/std.h"

#include "gamedata.h"
#include "scene.h"
#include "utility.h"

namespace se {

//class Cycle;

class SceneManager {
public:
    ~SceneManager();

    static Scene* activeScene;

    static bool sceneSet;

    template <class T>
    static T* LoadScene(std::string _name = "") {  // Adds a scene of class T

        // todo pause e restore dopo
        T* scene = new T();
        scene->name = (_name == "" ? util::classtitle<T>() : _name);

        if (sceneSet) {
            delete (scene);
            GameData::DestroyAll();
        }
        Setscene(scene);
        return scene;
    }

    static void Setscene(Scene*);
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
    static std::vector<Scene*> Scenes;
};

}  // namespace se
