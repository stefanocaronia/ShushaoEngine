#include "transform.h"
#include "spriterenderer.h"
#include "scenemanager.h"

#include <algorithm>
#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/string_cast.hpp>

using namespace std;
using namespace glm;

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

	void Transform::setParent(Transform* newpa, bool worldPositionStays) {
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

	void Transform::setPosition(vec3 position_) {
		localPosition = position_ - (!isAtRoot() ? parent->position : vec3(0));
	}

	void Transform::setLocalPosition(vec3 position_) {
		localPosition = position_;
	}

	void Transform::setLocalRotation(vec3 angles_) {
		localRotation = quat(angles_);
	}

	void Transform::setLocalRotation(quat rotation_) {
		localRotation = rotation_;
	}

	vec3 Transform::getEulerAngles() {
		return glm::eulerAngles(_rotation);
	}

	vec3 Transform::getLocalEulerAngles() {
		return glm::eulerAngles(localRotation);
	}

	void Transform::setupDirections() {
		_up = _rotation * UP;
		_right = _rotation * RIGHT;
		_forward = _rotation * FORWARD;
	}

	void Transform::setLocalScale(vec3 scale_) {
		localScale = scale_;
	}

	void Transform::setPivot(vec2 pivot_) {
		_pivot = {pivot_.x, pivot_.y, 0.0f};
	}

	void Transform::Awake() {
		// ...
	}

	void Transform::Update() {

		_position = getWorldPosition();
		_rotation = getWorldOrientation();
		setupDirections();

		mat4 M = getLocalToWorldMatrix() * translate(-pivot);
		mat4 P = SceneManager::activeScene->activeCamera->Projection;
		mat4 V = SceneManager::activeScene->activeCamera->getViewMatrix();

		_MVP = P * V * M;
	}

	mat4 Transform::getLocalToParentMatrix() {
		return translate(localPosition) * glm::toMat4(localRotation) * glm::scale(localScale);
	}

	mat4 Transform::getLocalToWorldMatrix() {
		if (isAtRoot()) {
			return getLocalToParentMatrix();
		} else {
			return parent->getLocalToWorldMatrix() * getLocalToParentMatrix();
		}
	}

	vec3 Transform::getWorldPosition() {
		vec4 p = getLocalToWorldMatrix() * vec4(0.0f, 0.0f, 0.0f, 1.0f);
		return vec3(p.x, p.y, p.z);
	}

	quat Transform::getWorldOrientation() {
		if (isAtRoot()) {
			return localRotation;
		} else {
			return localRotation * parent->rotation;
		}
		return quat();
	}

	mat4 Transform::getWorldToLocalMatrix() {
		return glm::inverse(getLocalToWorldMatrix());
	}

	const vec3 Transform::VEC3_ZERO = {0.0f, 0.0f, 0.0f};
	const vec3 Transform::VEC3_IDENTITY = {1.0f, 1.0f, 1.0f};
	const vec3 Transform::VEC3_IDENTITY2D = {1.0f, 1.0f, 0.0f};
	const vec3 Transform::UP = {0.0f, 1.0f, 0.0f};
	const vec3 Transform::DOWN = {0.0f, -1.0f, 0.0f};
	const vec3 Transform::FORWARD = {0.0f, 0.0f, 1.0f};
	const vec3 Transform::BACK = {0.0f, 0.0f, -1.0f};
	const vec3 Transform::RIGHT = {1.0f, 0.0f, 0.0f};
	const vec3 Transform::LEFT = {-1.0f, 0.0f, 0.0f};
	const quat Transform::QUATERNION_IDENTITY = {1.0f, 0.0f, 0.0f, 0.0f};
}
