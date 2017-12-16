#pragma once

#include "globals.h"

class Pancrazio : public Entity {
	public:
		Pancrazio();
		~Pancrazio();

		SpriteRenderer* sr;
		Rigidbody2D* rb;
		BoxCollider2D* collider;
		CircleCollider2D* circlec;
		Animation* animation;

	protected:



	private:
};
