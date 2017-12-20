#pragma once

#include "globals.h"


class Mover : public Program {

	public:


	protected:

		void Update();
		void Awake();

		void OnCollisionEnter2D(Collision2D&);
		void OnCollisionExit2D(Collision2D&);
		void OnCollisionStay2D(Collision2D&);

		void OnTriggerEnter2D(Collider2D&);
		void OnTriggerExit2D(Collider2D&);
		void OnTriggerStay2D(Collider2D&);

	private:

		float animTime;
		SpriteRenderer* sr = nullptr;
		Rigidbody2D* rb = nullptr;
};
