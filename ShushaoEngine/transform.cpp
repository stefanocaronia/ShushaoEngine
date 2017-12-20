#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "transform.h"
#include "scenemanager.h"
#include "utility.h"

#define FLIP -1;

namespace ShushaoEngine {

	Transform::Transform() {
		name = "Transform";
	}

	//{ #region parenting

	Transform* Transform::getParent() {
		return parent;
	}

	bool Transform::isAtRoot() {
		return (isRoot || (parent != nullptr && parent->isRoot));
	}

	void Transform::SetParent(Transform* newpa, bool worldPositionStays) {
		lock = true;
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
		lock = false;
	}

	void Transform::RemoveChild(Transform* t) {
		if (children.empty()) return;
		auto it = find(children.begin(), children.end(), t);
		if (it != children.end()) children.erase(it);
	}

	void Transform::AddChild(Transform* t) {
		if (children.empty()) {
			children.push_back(t);
			return;
		}
		auto it = find(children.begin(), children.end(), t);
		if (it == children.end()) children.push_back(t);
	}

	Transform* Transform::getChild(unsigned int index) {
		if (index >= children.size()) return nullptr;
		return children.at(index);
	}

	//}

	void Transform::SetPosition(glm::vec3 position_) {
		localPosition = position_ - (!isAtRoot() ? parent->position : glm::vec3(0));
		_position = GetWorldPosition();
		setupDirections();
	}

	void Transform::SetLocalPosition(glm::vec3 position_) {
		localPosition = position_;
		_position = GetWorldPosition();
		setupDirections();
	}

	void Transform::SetLocalRotation(glm::vec3 angles_) { // angles_ is in radians
		localRotation = glm::quat(angles_ * (DEGTORAD));
		_rotation = GetWorldOrientation();
		setupDirections();
	}

	void Transform::SetLocalRotation(glm::quat rotation_) {
		localRotation = rotation_;
		_rotation = GetWorldOrientation();
		setupDirections();
	}

	void Transform::SetRotation(glm::vec3 angles_) { // angles_ is in radians
		_rotation = glm::quat(angles_ * (DEGTORAD));
		localRotation = _rotation * parent->rotation;
		setupDirections();
	}

	void Transform::SetRotation(glm::quat rotation_) {
		_rotation = rotation_;
		localRotation = _rotation * parent->rotation;
		setupDirections();
	}

	glm::vec3 Transform::GetEulerAngles() {
		return glm::eulerAngles(_rotation) * RADTODEG;
		//return util::toEulerAngles(_rotation);
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
		localScale = scale_;
		_scale = GetWorldScale();
	}

	void Transform::SetPivot(glm::vec2 pivot_) {
		_pivot = {pivot_.x, pivot_.y, 0.0f};
	}

	void Transform::buildMVP() {
		glm::mat4 M = GetLocalToWorldMatrix() * glm::translate(glm::mat4(), -pivot);
		glm::mat4 P = SceneManager::activeScene->activeCamera->Projection;
		glm::mat4 V = SceneManager::activeScene->activeCamera->getViewMatrix();

		_MVP = P * V * M;
	}

	void Transform::Awake() {
		buildMVP();
	}

	void Transform::Update() {

		_position = GetWorldPosition();
		_rotation = GetWorldOrientation();
		setupDirections();

		buildMVP();
	}

	glm::mat4 Transform::GetLocalToParentMatrix() {
		return glm::translate(glm::mat4(), localPosition) * glm::toMat4(localRotation) * glm::scale(glm::mat4(), localScale);
	}

	glm::mat4 Transform::GetLocalToWorldMatrix() {
		if (isAtRoot()) {
			return GetLocalToParentMatrix();
		} else {
			return parent->GetLocalToWorldMatrix() * GetLocalToParentMatrix();
		}
	}

	glm::vec3 Transform::GetWorldPosition() {
		glm::vec4 p = GetLocalToWorldMatrix() * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
		return glm::vec3(p.x, p.y, p.z);
	}

	vec3 Transform::GetWorldScale() {
		if (isAtRoot()) {
			return localScale;
		} else {
			return localScale * parent->GetWorldScale();
		}
	}

	quat Transform::GetWorldOrientation() {
		if (isAtRoot()) {
			return localRotation;
		} else {
			return localRotation * parent->rotation;
		}
		return quat();
	}

	mat4 Transform::GetWorldToLocalMatrix() {
		return glm::inverse(GetLocalToWorldMatrix());
	}

	const vec3 Transform::VEC3_ZERO = {0.0f, 0.0f, 0.0f};
	const vec3 Transform::VEC3_IDENTITY = {1.0f, 1.0f, 1.0f};
	const vec3 Transform::VEC3_IDENTITY2D = {1.0f, 1.0f, 0.0f};
	const vec3 Transform::UP = {0.0f, 1.0f, 0.0f};
	const vec3 Transform::X = {1.0f, 0.0f, 0.0f};
	const vec3 Transform::Y = {0.0f, 1.0f, 0.0f};
	const vec3 Transform::Z = {0.0f, 0.0f, 1.0f};
	const vec3 Transform::DOWN = {0.0f, -1.0f, 0.0f};
	const vec3 Transform::FORWARD = {0.0f, 0.0f, 1.0f};
	const vec3 Transform::BACK = {0.0f, 0.0f, -1.0f};
	const vec3 Transform::RIGHT = {1.0f, 0.0f, 0.0f};
	const vec3 Transform::LEFT = {-1.0f, 0.0f, 0.0f};
	const quat Transform::QUATERNION_IDENTITY = {1.0f, 0.0f, 0.0f, 0.0f};
}
