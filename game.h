#pragma once

#include "globals.h"

class Game : public ShushaoEngine::Cycle {

	public:

		Game(string);
		~Game();

		string name;

	protected:

		void Awake();
		void Start();
		void GetInput();
		void FixedUpdate();
		void Update();
		void Render();
		void End();
};

