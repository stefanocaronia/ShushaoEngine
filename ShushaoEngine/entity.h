#pragma once

#include <string>
#include <iostream>

#include "debug.h"
#include "object.h"
#include "transform.h"
#include "spriterenderer.h"
#include "linerenderer.h"
#include "utility.h"
#include "component.h"

namespace ShushaoEngine {

	class Scene;
	class Transform;
	class SpriteRenderer;

	class Entity : public Object {

		public:

			Entity();
			Entity(std::string);

			~Entity();

			Transform* transform = nullptr;
			Scene* scene = nullptr;	// Scene that the Entity is part of.

			vector<Component*> Components;

			int layer;	// The layer the game object is in. A layer is in the range [0...31].
			std::string tag;		// The tag of this game object.
			vector<std::string> tags;		// The tag of this game object.

			bool activeInHierarchy;	// 	Is the Entity active in the scene?
			bool activeSelf;	// 	The local active state of this Entity. (Read Only)
			bool isStatic;	// 	Editor only API that specifies if a game object is static.

			void run(std::string);
			vector<Component*> GetActiveComponentsInChildren();
			void PrintHierarchy(int);
			bool isActiveInHierarchy();

			void BroadcastMessage(std::string methodName);	// Calls the method named methodName on every MonoBehaviour in this game object or any of its children.
			bool CompareTag(std::string t);	// Is this game object tagged with tag?

			template<class T>
			T* AddComponent(std::string _name = "") { // Adds a component class named className to the game object.
				T* component = new T();
				component->transform = transform;
				component->entity = this;
				component->name = (_name == "" ? util::classtitle<T>() : _name);
				Components.push_back(component);
				return component;
			}

			template<class T>
			T* GetComponent(std::string _name = "") {	// Returns the component of Type type if the game object has one attached, null if it doesn't.
				for(Component* component: Components)
					if (dynamic_cast<T*>(component)) {
						if (_name == "" || component->name == _name) return dynamic_cast<T*>(component);
					}
				//Debug::Log(ERROR, "Component " + _name + " (" + util::classtitle<T>() + ") non trovato", SOURCE);
				return nullptr;
			}

			template<class T>
			T* GetComponentInChildren();	// TODO: Returns the component of Type type in the GameObject or any of its children using depth first search.

			template<class T>
			T* GetComponentInParent();	// TODO: Returns the component of Type type in the Entity or any of its parents.

			template<class T>
			T* GetComponents();	// TODO: Returns all components of Type type in the Entity.

			template<class T>
			T* GetComponentsInChildren();	// TODO: Returns all components of Type type in the Entity or any of its children.

			template<class T>
			T* GetComponentsInParent(); // TODO: Returns all components of Type type in the Entity or any of its parents.

			void SendMessage(std::string);	// TODO: Calls the method named methodName on every MonoBehaviour in this game object.
			void SendMessageUpwards(std::string);	//  TODO: Calls the method named methodName on every MonoBehaviour in this game object and on every ancestor of the behaviour.
			void SetActive(bool);	// Activates/Deactivates the Entity.

			static Entity* Find(std::string); // Finds a Entity by name and returns it.
			static Entity* FindEntitysWithTag(std::string); // Returns a list of active Entitys tagged tag. Returns empty array if no Entity was found.
			static Entity* FindWithTag(std::string);	//	Returns one active Entity tagged tag. Returns null if no Entity was found.


			void setParent(Entity*);
	};

}
