#pragma once

#include <Box2D/Box2D.h>

#include "component.h"

namespace ShushaoEngine {

	class Rigidbody2D;

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

			void Awake();
			void Start();

			void Attach();
			void Reset();

			virtual void resetShape() = 0;

			//void FixedUpdate();
			void OnDestroy();

		protected:

		private:

	};


	class PolygonCollider2D : public Collider2D {

		public:

			b2PolygonShape shape;
			void setShape(std::vector<glm::vec2>);

			void resetShape() {}

		protected:

	};

	class BoxCollider2D : public Collider2D {

		public:

			glm::vec2 boxHalfSize;

			b2PolygonShape shape;
			void setShape(glm::vec2);

			void resetShape();

		protected:

	};

	class CircleCollider2D : public Collider2D {

		public:

			b2CircleShape shape;
			void setShape(glm::vec2, float);
			void resetShape() {}

		protected:


	};

	class EdgeCollider2D : public Collider2D {

		public:

			b2EdgeShape shape;

			void setShape(glm::vec2, glm::vec2);

			void resetShape() {}

		protected:


	};
}
