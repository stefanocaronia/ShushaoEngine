#pragma once

#include <string>

using namespace std;

namespace ShushaoEngine {

	class Cycle {

		public:

			virtual void run();
			virtual void exit();
			virtual bool init();

		protected:

			// pure virtual (devo implementare x forza)
			virtual void Awake() = 0;
			virtual void Start() = 0;
			virtual void Input() = 0;
			virtual void Update() = 0;
			virtual void Render() = 0;
			virtual void FixedUpdate() = 0;
			virtual void End() = 0;

			virtual void updateCycle();
			virtual void renderCycle();
			virtual void fixedUpdateCycle();

			bool RUNNING = true;
			bool READY = false;

			bool keys[350];

	};


}

