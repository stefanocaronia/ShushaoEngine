#pragma once

#include <vector>

#include "cycle.h"
#include "object.h"
#include "glmanager.h"
#include "scenemanager.h"

using namespace std;

namespace ShushaoEngine {

	class Object;

	class GLGame;



	class GLGame : public Cycle {

		public:

			GLGame(string);
			~GLGame();

			void run();
			void exit();
			bool init();

			string TITLE;

			GLManager& GL = GLManager::GetInstance();
			SceneManager& Scenes = SceneManager::GetInstance(this);

		protected:

			void renderCycle();
			void updateCycle();
			void fixedUpdateCycle();

	};

}
