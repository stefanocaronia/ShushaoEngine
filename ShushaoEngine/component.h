#pragma once

#include <string>
#include <vector>
#include <map>

#include "object.h"

using namespace std;

namespace ShushaoEngine {

	class Entity;
	class Transform;

	class Component : public Object	{

		public:

			Component();
			virtual ~Component();

			bool enabled = true;
			bool isActiveAndEnabled();

			Entity* entity;
			Transform* transform;

			string tag;

			// usati in Renderer ma necessari da qui
			int sortingLayerID = 0; //Unique ID of the Renderer's sorting layer.
			int sortingOrder = 0; //Renderer's order within a sorting layer.

			vector<string>* tags;

			void BroadcastMessage();	// Calls the method named methodName on every MonoBehaviour in this game object or any of its children.
			bool CompareTag(string);	// Is this game object tagged with tag ?

			template<class T>
			T* GetComponent();	// Returns the component of Type type if the game object has one attached, null if it doesn't.

			template<class T>
			T* GetComponentInChildren();	// Returns the component of Type type in the Entity or any of its children using depth first search.

			template<class T>
			T* GetComponentInParent();	// Returns the component of Type type in the Entity or any of its parents.

			template<class T>
			T* GetComponents();	// Returns all components of Type type in the Entity.

			template<class T>
			T* GetComponentsInChildren();	// Returns all components of Type type in the Entity or any of its children.

			template<class T>
			T* GetComponentsInParent(); // Returns all components of Type type in the Entity or any of its parents.

			vector<Component*> GetActiveComponentsInChildren();

			void SendMessage(string methodName);	// Calls the method named methodName on every MonoBehaviour in this game object.
			void SendMessageUpwards(string methodName);	// Calls the method named methodName on every MonoBehaviour in this game object and on every ancestor of the behaviour.

			virtual void init();
			virtual void exit();
			virtual void update();
			virtual void render();
			virtual void fixed();

			//void run(BaseCycle);
			void run(string);
			virtual void call(string);

			//void CancelInvoke(); //	Cancels all Invoke calls on this MonoBehaviour.
			//void Invoke(); //	Invokes the method methodName in time seconds.
			//void InvokeRepeating(); //	Invokes the method methodName in time seconds, then repeatedly every repeatRate seconds.
			//void IsInvoking(); //	Is any invoke on methodName pending?
			// StartCoroutine(); //	Starts a coroutine.
			// StopAllCoroutines(); //	Stops all coroutines running on this behaviour.
			// StopCoroutine(); //	Stops the first coroutine named methodName, or the coroutine stored in routine running on this behaviour.

		protected:

			bool started;

			// messages

			void Awake(); // Awake is called when the script instance is being loaded.
			void Start(); // Start is called on the frame when a script is enabled just before any of the Update methods is called the first time.
			void Update(); // Update is called every frame, if the MonoBehaviour is enabled.
			void FixedUpdate(); // This function is called every fixed framerate frame, if the MonoBehaviour is enabled.
			void LateUpdate(); // LateUpdate is called every frame, if the Behaviour is enabled.
			void OnPostRender(); // OnPostRender is called after a camera finished rendering the scene.
			void OnEnable(); // This function is called when the object becomes enabled and active.
			void OnDestroy(); // This function is called when the MonoBehaviour will be destroyed.
			void OnDisable(); // This function is called when the behaviour becomes disabled () or inactive.

	};

}
