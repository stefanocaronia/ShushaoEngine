#pragma once

#include <string>
#include <vector>

#include "object.h"

namespace ShushaoEngine {

	class Entity;
	class Transform;
	class Collision2D;
	class Collider2D;

	class Component : public Object	{

		public:

			Component();
			virtual ~Component();

			Entity* entity;
			Transform* transform;
			std::string tag;

			bool enabled = true;

			void BroadcastMessage();	// Calls the method named methodName on every MonoBehaviour in this game object or any of its children.

			std::vector<Component*> GetActiveComponentsInChildren();
			bool isActiveAndEnabled();

			void BroadcastMessage(std::string methodName);	// Calls the method named methodName on every MonoBehaviour in this game object or any of its children.
			void SendMessage(std::string methodName); // Calls the method named methodName on every MonoBehaviour in this game object.
			void SendMessageUpwards(std::string methodName);	// Calls the method named methodName on every MonoBehaviour in this game object and on every ancestor of the behaviour.

			//void run(BaseCycle);
			void run(std::string);
			virtual void call(std::string);

			virtual void ReceiveMessage(std::string methodName, Object& parameter);
			virtual void ReceiveMessage(std::string methodName);

			void Enable();
			void Disable();

			std::string getTitle();


			/* impossibile per riferimenti circolari?

			template<class T>
			T* GetComponent(std::string _name = "") {	// Returns the component of Type type if the game object has one attached, null if it doesn't.
				return entity->GetComponent<T>(_name);
			}*/


		protected:

			virtual void Awake(); // Awake is called when the script instance is being loaded.
			virtual void Start(); // Start is called on the frame when a script is enabled just before any of the Update methods is called the first time.
			virtual void Update(); // Update is called every frame, if the MonoBehaviour is enabled.
			virtual void Render(); // Render is called every frame, if the MonoBehaviour is enabled.
			virtual void FixedUpdate(); // This function is called every fixed framerate frame, if the MonoBehaviour is enabled.
			virtual void LateUpdate(); // LateUpdate is called every frame, if the Behaviour is enabled.
			virtual void OnPostRender(); // OnPostRender is called after a camera finished rendering the scene.
			virtual void OnEnable(); // This function is called when the object becomes enabled and active.
			virtual void OnDestroy(); // This function is called when the MonoBehaviour will be destroyed.
			virtual void OnDisable(); // This function is called when the behaviour becomes disabled () or inactive.

			// messages
			virtual void OnCollisionEnter2D(Collision2D&);
			virtual void OnCollisionExit2D(Collision2D&);
			virtual void OnCollisionStay2D(Collision2D&);
			virtual void OnTriggerEnter2D(Collider2D&);
			virtual void OnTriggerExit2D(Collider2D&);
			virtual void OnTriggerStay2D(Collider2D&);

		private:

			bool currentEnable;
			bool started;

			virtual void init();
			virtual void update();
			virtual void fixed();
			virtual void render();
			virtual void exit();



	};

}
