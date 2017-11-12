#pragma once

#include <string>
#include <vector>
#include <map>

#include "object.h"
#include "component.h"
#include "camera.h"
#include "scene.h"

using namespace std;

namespace ShushaoEngine {

	class GameData {
		public:

			static int GenerateObjectID();
			static int RegisterObject(Object*);

			static void UnRegisterObject(int);
			static void RegisterComponent(Component*);

			static void PrintAllObjects();
			static Object* GetObjectWithID(int);

			static void DestroyAll();

			/*
			template<class T>
			vector<Object*> GameData::GetObjectsOfType() {	// Returns the component of Type type if the game object has one attached, null if it doesn't.
				vector<Object*> results;
				vector<Object*>::iterator it = std::find_if (Objects.begin(), Objects.end(), [id](const Object* obj){
					if (dynamic_cast<T*>(component))
						results.push_back(dynamic_cast<T*>(obj));
				});
				return results;
			}			*/

			static Camera* activeCamera;
			static Scene* activeScene;

			static vector<Object*> Objects;
			static vector<Component*> Components;



	};

}
