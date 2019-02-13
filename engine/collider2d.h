#pragma once

#include <Box2D/Box2D.h>

#include "component.h"

namespace se {

	class Rigidbody2D;
	class Collider2D;

	class Collider2D : public Component {

		public:

			Collider2D();

			Rigidbody2D* rigidbody = nullptr;
			b2FixtureDef fixtureDef;
			b2Fixture* fixture = nullptr;

			glm::vec2 scale = {1.0f, 1.0f};

			float density = 1.0f;;
			float friction = 0.3f;
			float restitution = 0.6f;

			bool isSensor = false;

			void SetDensity(float);
			void SetRestitution(float);
			void SetFriction(float);
			void SetSensor(bool);

			void Awake();
			void Start();

			void Attach();
			void Reset();

			virtual void ResetShape() {}

			void FixedUpdate();
			void OnDestroy();

			void ColliderEnter(Collider2D*);
			void ColliderExit(Collider2D*);

		protected:

			std::vector<Collider2D*> colliders;

		private:

	};

	class PolygonCollider2D : public Collider2D {

		public:

			b2PolygonShape shape;
			void SetShape(std::vector<glm::vec2>);

			void ResetShape() {}

		protected:

	};

	class BoxCollider2D : public Collider2D {

		public:

			glm::vec2 boxHalfSize;

			b2PolygonShape shape;
			void SetShape(glm::vec2);
			void ResetShape();

		protected:

	};

	class CircleCollider2D : public Collider2D {

		public:

			b2CircleShape shape;
			void SetShape(glm::vec2, float);
			void ResetShape();

		protected:

			glm::vec2 position;
			float radius;

	};

	class EdgeCollider2D : public Collider2D {

		public:

			b2EdgeShape shape;

			void SetShape(glm::vec2, glm::vec2);

			void ResetShape() {}

		protected:


	};
}
