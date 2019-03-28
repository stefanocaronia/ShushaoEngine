#pragma once

#include <string>

namespace se {



	class Cycle {

		public:

			enum class Stage {
				INIT,
				UPDATE,
				FIXED,
				RENDER,
				EXIT
			};

			Cycle(std::string);
			~Cycle();

			std::string name;

			bool init();
			void run();
			void stop();

		protected:

			// pure virtual (devo implementare x forza)
			virtual void Awake() = 0;
			virtual void Start() = 0;
			virtual void GetInput() = 0;
			virtual void Update() = 0;
			virtual void Render() = 0;
			virtual void FixedUpdate() = 0;
			virtual void End() = 0;

			bool RUNNING = true;
			bool READY = false;

			bool keys[350];

		private:

			void update();
			void render();
			void fixed();
			void exit();
	};
}

extern se::Cycle* GAME;
