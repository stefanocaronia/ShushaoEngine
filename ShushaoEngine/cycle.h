#pragma once

#include <string>

using namespace std;

namespace ShushaoEngine {

	class Cycle {

		public:

			Cycle(string);
			~Cycle();

			string name;

			virtual void run();
			virtual void exit();
			virtual void init();

			static string INIT;
			static string UPDATE;
			static string FIXED;
			static string RENDER;
			static string EXIT;

		protected:

			// pure virtual (devo implementare x forza)
			virtual void Awake() = 0;
			virtual void Start() = 0;
			virtual void Input() = 0;
			virtual void Update() = 0;
			virtual void Render() = 0;
			virtual void FixedUpdate() = 0;
			virtual void End() = 0;

			virtual void update();
			virtual void render();
			virtual void fixed();

			bool RUNNING = true;
			bool READY = false;

			bool keys[350];

	};


}

