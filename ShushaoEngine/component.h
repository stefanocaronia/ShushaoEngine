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

			Entity* entity;
			Transform* transform;
			string tag;

			bool enabled = true;
			bool started;

			void BroadcastMessage();	// Calls the method named methodName on every MonoBehaviour in this game object or any of its children.

			vector<Component*> GetActiveComponentsInChildren();
			bool isActiveAndEnabled();

			void BroadcastMessage(string methodName);	// Calls the method named methodName on every MonoBehaviour in this game object or any of its children.
			void SendMessage(string methodName);	// Calls the method named methodName on every MonoBehaviour in this game object.
			void SendMessageUpwards(string methodName);	// Calls the method named methodName on every MonoBehaviour in this game object and on every ancestor of the behaviour.

			//void run(BaseCycle);
			void run(string);
			virtual void call(string);

			void Enable();
			void Disable();

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

		private:

			bool currentEnable;

			virtual void init();
			virtual void update();
			virtual void fixed();
			virtual void render();
			virtual void exit();
	};

}
