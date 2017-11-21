#pragma once

#include "globals.h"

class Mover : public Program {

	public:



	protected:

		void Update();
		void Awake();


	private:
		float animTime;
		SpriteRenderer* sr = nullptr;
};
