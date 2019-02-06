#pragma once

#include "globals.h"

class Pancrazio : public ShushaoEngine::Entity {
	public:
		Pancrazio();
		~Pancrazio();

		ShushaoEngine::SpriteRenderer* sr;
		ShushaoEngine::Rigidbody2D* rb;
		ShushaoEngine::BoxCollider2D* collider;
		ShushaoEngine::CircleCollider2D* circlec;
		ShushaoEngine::Animation* animation;

	protected:



	private:
};
