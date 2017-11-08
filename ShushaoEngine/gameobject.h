#pragma once

#include <string>

#include "object.h"
#include "transform.h"
#include "component.h"
#include "spriterenderer.h"

using namespace std;

namespace ShushaoEngine {

	class Scene;
	class Transform;
	class SpriteRenderer;

	class GameObject : public Object {

		public:

			GameObject();
			GameObject(string);

			~GameObject();

			Transform* transform;

			bool activeInHierarchy;	// 	Is the GameObject active in the scene?
			bool activeSelf;	// 	The local active state of this GameObject. (Read Only)
			bool isStatic;	// 	Editor only API that specifies if a game object is static.

			int layer;	// The layer the game object is in. A layer is in the range [0...31].
			Scene* scene;	// Scene that the GameObject is part of.

			string tag;		// The tag of this game object.
			vector<string> tags;		// The tag of this game object.

			void run(BaseCycle);

			vector<Component*> GetChildrenActiveComponents();

			bool GetActiveState();

			template<class T>
			T* AddComponent() { // Adds a component class named className to the game object.
				T* component = new T();
				component->transform = transform;
				component->gameObject = this;
				Components.push_back(component);
				return component;
			}


			void BroadcastMessage(string methodName);	// Calls the method named methodName on every MonoBehaviour in this game object or any of its children.
			bool CompareTag(string t);	// Is this game object tagged with tag?

			template<class T>
			T* GetComponent() {	// Returns the component of Type type if the game object has one attached, null if it doesn't.
				for(Component* component: Components) {
					if (dynamic_cast<T*>(component))
						return dynamic_cast<T*>(component);
				}
				return nullptr;
			}

			template<class T>
			T* GetComponentInChildren();	// Returns the component of Type type in the GameObject or any of its children using depth first search.

			template<class T>
			T* GetComponentInParent();	// Returns the component of Type type in the GameObject or any of its parents.

			template<class T>
			T* GetComponents();	// Returns all components of Type type in the GameObject.

			template<class T>
			T* GetComponentsInChildren();	// Returns all components of Type type in the GameObject or any of its children.

			template<class T>
			T* GetComponentsInParent(); // Returns all components of Type type in the GameObject or any of its parents.

			void SendMessage(string);	// Calls the method named methodName on every MonoBehaviour in this game object.
			void SendMessageUpwards(string);	// Calls the method named methodName on every MonoBehaviour in this game object and on every ancestor of the behaviour.
			void SetActive(bool);	// Activates/Deactivates the GameObject.

			static GameObject* Find(string); // Finds a GameObject by name and returns it.
			static GameObject* FindGameObjectsWithTag(string); // Returns a list of active GameObjects tagged tag. Returns empty array if no GameObject was found.
			static GameObject* FindWithTag(string);	//	Returns one active GameObject tagged tag. Returns null if no GameObject was found.

			vector<Component*> Components;
	};

}
