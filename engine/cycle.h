#pragma once

#include <string>

namespace ShushaoEngine {

	class Cycle {

		public:

			Cycle(std::string);
			~Cycle();

			std::string name;

			bool init();
			void run();
			void stop();

			static std::string INIT;
			static std::string UPDATE;
			static std::string FIXED;
			static std::string RENDER;
			static std::string EXIT;

		protected:

			// pure virtual (devo implementare x forza)
			virtual void Awake() = 0;
			virtual void Start() = 0;
			virtual void Input() = 0;
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

extern ShushaoEngine::Cycle* GAME;
