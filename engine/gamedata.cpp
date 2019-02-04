#include <vector>
#include <algorithm>
#include <string>

#include "gamedata.h"
#include "camera.h"
#include "scene.h"
#include "object.h"
#include "component.h"

using namespace std;

namespace ShushaoEngine {

	int GameData::GenerateObjectID() {
		if (Objects.size() > 0) {
			return Objects.back()->GetInstanceID() + 1;
		}
		return 1;
	}

	int GameData::RegisterObject(Object* obj) {
		obj->InstanceID = GenerateObjectID();
		Objects.push_back(obj);
		return obj->InstanceID;
	}

	void GameData::UnRegisterObject(int id) {
		std::vector<Object*>::iterator it = std::find_if (Objects.begin(), Objects.end(), [id](const Object* obj){
			return obj->InstanceID == id;
		});
		Objects.erase(it);
	}

	void GameData::RegisterComponent(Component* obj) {
		Components.push_back(obj);
	}

	void GameData::PrintAllObjects() {
		for (Object* obj : Objects) {
			cout << obj->GetInstanceID() << ": " << obj->name << endl;
		}
	}

	Object* GameData::GetObjectWithID(int id) {
        std::vector<Object*>::iterator it = std::find_if (Objects.begin(), Objects.end(), [id](const Object* obj){
			return obj->InstanceID == id;
		});

		return *it;
	}

	void GameData::DestroyAll() {
		for(Object* obj : Objects) delete(obj);
		for(Component* obj : Components) delete(obj);
		Components.clear();
		Objects.clear();
	}

	// inizializations of members

	Scene* GameData::activeScene;
	Camera* GameData::activeCamera;

	// FORSE DA ELIMINARE, SONO GESTITI NELLE SCENE
	std::vector<Object*> GameData::Objects;
	std::vector<Component*> GameData::Components;


//
	//for (int i = 1; i < 31; i++) {
	//	GameData::Layers[i] = "";
	//}
	//GameData::SortingLayers[0] = "Default";

}
