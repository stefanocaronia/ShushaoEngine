#pragma once

#include "globals.h"

class Game : public se::Cycle {

	public:

		bool perspectiveTest = false;

	protected:

		bool InitResources();
		bool InitConfig();
		bool InitMapping();
		bool InitScene();

		void GetInput();
};

