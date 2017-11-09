#pragma once

#include <string>

#include "cycle.h"

using namespace ShushaoEngine;

class Game : public Cycle {

	public:

		Game(string);
		~Game();

		string name;

	protected:

		void Awake();
		void Start();
		void Input();
		void FixedUpdate();
		void Update();
		void Render();
		void End();
};

