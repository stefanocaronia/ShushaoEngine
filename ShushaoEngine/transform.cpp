#include "transform.h"
#include "spriterenderer.h"
#include "scenemanager.h"

#include <algorithm>
#include <iostream>
#include <vector>

#include <glm.hpp>
#include <gtx/quaternion.hpp>
#include <gtx/euler_angles.hpp>
#include "gtx/string_cast.hpp"

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

	bool Transform::hasParent() {
		return (parent != nullptr);
	}

	bool Transform::hasRootParent() {
		return (parent != nullptr && parent->isRoot);
	}

	bool Transform::isChild() {
		return (parent != nullptr && !parent->isRoot);
	}

	bool Transform::onRoot() {
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
		localPosition = position_ - (isChild() ? parent->position : vec3(0));
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

		_M = getLocalToWorldMatrix() * translate(-pivot);
		_position = (onRoot() ? localPosition : toWorld(localPosition));

		_MVP = SceneManager::activeScene->activeCamera->Projection * SceneManager::activeScene->activeCamera->getViewMatrix() * M;

		setupDirections();
	}

	mat4 Transform::getLocalToParentMatrix() {
		return translate(localPosition) * glm::toMat4(localRotation) * glm::scale(localScale);
	}

	mat4 Transform::getLocalToWorldMatrix() {
		if (onRoot()) {
			return getLocalToParentMatrix();
		} else {
			return parent->getLocalToWorldMatrix() * getLocalToParentMatrix();
		}
	}

	mat4 Transform::getWorldToLocalMatrix() {
		return glm::inverse(getLocalToWorldMatrix());
	}

	vec3 Transform::toWorld(vec3 point) {
		vec4 result = getLocalToWorldMatrix() * vec4(point, 1.0f);
		return vec3(result.x, result.y, result.z);
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
