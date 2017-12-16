#pragma once

#include "globals.h"

class Mover : public Program {

	public:

	protected:

		void Update();
		void Awake();

		void OnCollisionEnter2D(Collision2D*);

	private:

		float animTime;
		SpriteRenderer* sr = nullptr;
};
