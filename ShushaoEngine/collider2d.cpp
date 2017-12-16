#include "collider2d.h"
#include "rigidbody2d.h"
#include "transform.h"
#include "entity.h"

namespace ShushaoEngine {

	//{ #region Collider2D (base virtual class)

	Collider2D::Collider2D() {
		fixtureDef.density = density;
		fixtureDef.friction = friction;
		fixtureDef.restitution = restitution;
		fixtureDef.isSensor = isSensor;
		fixtureDef.userData = this;
	}

	void Collider2D::OnDestroy() {
		/*if (fixture != nullptr && rigidbody != nullptr) {
			rigidbody->body->DestroyFixture(fixture);
		}*/
	}

	void Collider2D::SetDensity(float density_) {
		density = density_;
		if (fixture != nullptr) fixture->SetDensity(density);
	}

	void Collider2D::SetRestitution(float restitution_) {
		restitution = restitution_;
		if (fixture != nullptr) fixture->SetRestitution(restitution);
	}

	void Collider2D::SetFriction(float friction_) {
		friction = friction_;
		if (fixture != nullptr) fixture->SetFriction(friction);
	}

	void Collider2D::Awake() {
		scale = {transform->scale.x, transform->scale.y};
	}

	void Collider2D::Start() {
		Attach();
	}

	void Collider2D::Attach() {
		rigidbody = entity->GetComponent<Rigidbody2D>();
		if (rigidbody == nullptr || rigidbody->body == nullptr)
			return;
		cout << "creo la fixture di " << entity->name << endl;
		fixture = rigidbody->body->CreateFixture(&fixtureDef);
	}

	void Collider2D::Reset() {
        rigidbody->body->DestroyFixture(fixture);
        fixture = rigidbody->body->CreateFixture(&fixtureDef);
	}

	//}

	//{ #region CircleCollider2D

	void CircleCollider2D::setShape(glm::vec2 position, float radius) {
		shape.m_p.Set(position.x, position.y);
		shape.m_radius = radius;
		fixtureDef.shape = &shape;
	}

	//}

	//{ #region BoxCollider2D

	void BoxCollider2D::setShape(glm::vec2 hsize) {
		cout << "setto la shape di " << entity->name << endl;
		boxHalfSize = hsize;
        shape.SetAsBox(boxHalfSize.x * scale.x, boxHalfSize.y * scale.y);
        fixtureDef.shape = &shape;
	}

	void BoxCollider2D::resetShape() {
		cout << "resetto la shape di " << entity->name << endl;
		scale = {transform->scale.x, transform->scale.y};
		cout << "nuova scale: " << scale.x << endl;
		shape.SetAsBox(boxHalfSize.x * scale.x, boxHalfSize.y * scale.y);
	}

	//}

	//{ #region EdgeCollider2D

	void EdgeCollider2D::setShape(glm::vec2 start, glm::vec2 end) {
		shape.Set(b2Vec2(start.x, start.y), b2Vec2(end.x, end.y));
		fixtureDef.shape = &shape;
	}

	//}

	//{ #region PolygonCollider2D

	void PolygonCollider2D::setShape(std::vector<glm::vec2>) {}

	//}
}
