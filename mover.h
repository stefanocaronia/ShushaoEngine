#pragma once

#include "globals.h"

class Mover : public ShushaoEngine::Program {

	public:


	protected:

		void Update();
		void Awake();

		void OnCollisionEnter2D(ShushaoEngine::Collision2D&);
		void OnCollisionExit2D(ShushaoEngine::Collision2D&);
		void OnCollisionStay2D(ShushaoEngine::Collision2D&);

		void OnTriggerEnter2D(ShushaoEngine::Collider2D&);
		void OnTriggerExit2D(ShushaoEngine::Collider2D&);
		void OnTriggerStay2D(ShushaoEngine::Collider2D&);

	private:

		float animTime;
		ShushaoEngine::SpriteRenderer* sr = nullptr;
		ShushaoEngine::Rigidbody2D* rb = nullptr;
};
