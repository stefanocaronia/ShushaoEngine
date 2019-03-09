#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "transform.h"
#include "scenemanager.h"
#include "utility.h"

namespace se {

	Transform::Transform() {
		name = "Transform";
	}

	//{ #region parenting

	Transform* Transform::GetParent() {
		return parent;
	}

	bool Transform::isAtRoot() {
		return (parent == nullptr || isRoot || (parent != nullptr && parent->isRoot));
	}

	void Transform::SetParent(Transform* newpa, bool worldPositionStays) {

		if (parent != nullptr) {
			parent->RemoveChild(this);
		}

		parent = newpa;

		if (worldPositionStays) {
			localPosition = _position - parent->position;
		} else {
			localPosition = VEC3_ZERO;
		}

		parent->AddChild(this);
		matrixInvalid = true;
	}

	void Transform::RemoveChild(Transform* t) {
		if (children.empty()) return;
		auto it = find(children.begin(), children.end(), t);
		if (it != children.end()) {
			children.erase(it);
		}
	}

	void Transform::AddChild(Transform* t) {
		if (children.empty()) {
			children.push_back(t);
			return;
		}
		auto it = find(children.begin(), children.end(), t);
		if (it == children.end()) children.push_back(t);
	}

	Transform* Transform::GetChild(unsigned int index) {
		if (index >= children.size()) return nullptr;
		return children.at(index);
	}

	vector<Transform*> Transform::GetParents() {
		vector<Transform*> parents;
		if (isAtRoot()) return parents;

		Transform* p = parent;
		while (p != nullptr && !p->isRoot) {
			parents.push_back(p);
			p = p->GetParent();
		}

		return parents;
	}

	//}

	void Transform::Invalidate() {
		if (!matrixInvalid) {
			matrixInvalid = true;
			inverseMatrixInvalid = true;
		}

		for (Transform* child : children) {
			child->Invalidate();
		}
	}

	//{ #region position

	void Transform::SetPosition(glm::vec3 position_) {
		if (isRoot) return;
		origin = WORLD;
		Invalidate();
		//localPosition = isAtRoot() ? position_ : parent->position - position_;
		_position = position_;
		setupDirections();
	}

	void Transform::SetLocalPosition(glm::vec3 position_) {
		if (isRoot) return;
		origin = LOCAL;
		localPosition = position_;
		Invalidate();
		_position = GetWorldPosition();
		setupDirections();
	}

	void Transform::SetLocalRotation(glm::vec3 angles_) { // angles_ is in radians
		if (isRoot) return;
		origin = LOCAL;
		localRotation = glm::quat(angles_ * DEGTORAD);
		Invalidate();
		_rotation = GetWorldOrientation();
		setupDirections();
	}

	void Transform::SetLocalRotation(glm::quat rotation_) {
		if (isRoot) return;
		origin = LOCAL;
		localRotation = rotation_;
		Invalidate();
		_rotation = GetWorldOrientation();
		setupDirections();
	}

	void Transform::SetRotation(glm::vec3 angles_) { // angles_ is in radians
		if (isRoot) return;
		origin = WORLD;
		_rotation = glm::quat(angles_ * DEGTORAD);
		//localRotation = _rotation;
		setupDirections();
	}

	void Transform::SetRotation(glm::quat rotation_) {
		if (isRoot) return;
		origin = WORLD;
		_rotation = rotation_;
		Invalidate();
		//localRotation = _rotation * parent->rotation;
		setupDirections();
	}

	glm::vec3 Transform::GetEulerAngles() {
		return glm::eulerAngles(rotation) * RADTODEG;
	}

	glm::vec3 Transform::GetLocalEulerAngles() {
		return glm::eulerAngles(localRotation) * RADTODEG;
	}

	void Transform::setupDirections() {
		_up = _rotation * UP;
		_right = _rotation * RIGHT;
		_forward = _rotation * FORWARD;
	}

	void Transform::SetLocalScale(glm::vec3 scale_) {
		if (isRoot) return;
		localScale = scale_;
		_scale = GetWorldScale();
	}

	void Transform::SetPivot(glm::vec2 pivot_) {
		if (isRoot) return;
		_pivot = {pivot_.x, pivot_.y, 0.0f};
	}

	//}

	void Transform::buildMVP() {
		glm::mat4 M = GetLocalToWorldMatrix();
		glm::mat4 P = SceneManager::activeScene->activeCamera->Projection;
		glm::mat4 V = SceneManager::activeScene->activeCamera->getViewMatrix();
		_MVP = P * V * M;
	}

	GLfloat* Transform::uMVP() {
		return &_MVP[0][0];
	}

	GLfloat* Transform::uM() {
		glm::mat4 M = GetLocalToWorldMatrix();
		return &M[0][0];
	}

	void Transform::Awake() {
		buildMVP();
		Invalidate();
	}

	void Transform::Update() {

		if (origin == LOCAL) {
			_position = GetWorldPosition();
			_rotation = GetWorldOrientation();
		}

		setupDirections();

		buildMVP();
	}

	glm::mat4 Transform::GetLocalToParentMatrix() {
		return _localToParentMatrix = glm::translate(glm::mat4(), localPosition) * glm::toMat4(localRotation) * glm::scale(glm::mat4(), localScale);
	}

	glm::mat4 Transform::GetRootMatrix() {
		return glm::translate(glm::mat4(), _position) * glm::toMat4(_rotation) * glm::scale(glm::mat4(), localScale);
	}

	glm::mat4 Transform::GetLocalToWorldMatrix() {
		if (matrixInvalid) {
			if (origin == WORLD) {
				_localToWorldMatrix = GetRootMatrix();
			} else if (isAtRoot()) {
				_localToWorldMatrix = GetLocalToParentMatrix();
			} else {
				_localToWorldMatrix = parent->GetLocalToWorldMatrix() * GetLocalToParentMatrix();
			}
			matrixInvalid = false;
		}
		return _localToWorldMatrix;
	}

	glm::mat4 Transform::GetWorldToLocalMatrix() {

		/*if (inverseMatrixInvalid) {
			_worldToLocalMatrix = glm::inverse(GetLocalToWorldMatrix());
			inverseMatrixInvalid = false;
		}
		return _worldToLocalMatrix;*/

		if (inverseMatrixInvalid) {
			if (isAtRoot()) {
				_worldToLocalMatrix = glm::mat4();
			} else {
				_worldToLocalMatrix =  glm::toMat4(parent->rotation) * glm::translate(glm::mat4(), -parent->position);
			}
			inverseMatrixInvalid = false;
		}
		return _worldToLocalMatrix;
	}

	glm::vec3 Transform::GetWorldPosition() {
		glm::vec4 p = GetLocalToWorldMatrix() * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
		return glm::vec3(p.x, p.y, p.z);
	}

	glm::vec3 Transform::GetLocalPosition(glm::vec3 position_) {
		glm::vec4 p = GetWorldToLocalMatrix() * glm::vec4(position_.x, position_.y, position_.z, 1.0f);
		return glm::vec3(p.x, p.y, p.z);
	}

	glm::vec3 Transform::GetWorldScale() {
		if (isAtRoot()) {
			return localScale;
		} else {
			return localScale * parent->GetWorldScale();
		}
	}

	glm::quat Transform::GetWorldOrientation() {
		if (isAtRoot()) {
			return localRotation;
		} else {
			return localRotation * parent->rotation;
		}
		return glm::quat();
	}

	const glm::vec3 Transform::VEC3_ZERO = {0.0f, 0.0f, 0.0f};
	const glm::vec3 Transform::VEC3_IDENTITY = {1.0f, 1.0f, 1.0f};
	const glm::vec3 Transform::VEC3_IDENTITY2D = {1.0f, 1.0f, 0.0f};
	const glm::vec3 Transform::UP = {0.0f, 1.0f, 0.0f};
	const glm::vec3 Transform::AXIS_X = {1.0f, 0.0f, 0.0f};
	const glm::vec3 Transform::AXIS_Y = {0.0f, 1.0f, 0.0f};
	const glm::vec3 Transform::AXIS_Z = {0.0f, 0.0f, 1.0f};
	const glm::vec3 Transform::DOWN = {0.0f, -1.0f, 0.0f};
	const glm::vec3 Transform::FORWARD = {0.0f, 0.0f, 1.0f};
	const glm::vec3 Transform::BACK = {0.0f, 0.0f, -1.0f};
	const glm::vec3 Transform::RIGHT = {1.0f, 0.0f, 0.0f};
	const glm::vec3 Transform::LEFT = {-1.0f, 0.0f, 0.0f};
	const glm::quat Transform::QUATERNION_IDENTITY = {1.0f, 0.0f, 0.0f, 0.0f};
}
