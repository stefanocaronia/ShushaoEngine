#pragma once

#include <string>

#include "glgame.h"

using namespace ShushaoEngine;

class Game : public GLGame {

	public:

		Game(string);
		~Game();

		string TITLE;

	protected:

		void Awake();
		void Start();
		void Input();
		void FixedUpdate();
		void Update();
		void Render();
		void End();
};

