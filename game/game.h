#pragma once

#include "globals.h"

class Game : public se::Cycle {

	public:

		Game(string);
		string name;

		bool perspectiveTest = false;

	protected:

		void Awake();
		void Start();
		void GetInput();
		void FixedUpdate();
		void Update();
		void Render();
		void End();
};

