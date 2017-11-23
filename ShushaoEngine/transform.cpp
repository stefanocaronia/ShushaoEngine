#include "transform.h"
#include "spriterenderer.h"
#include "scenemanager.h"

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using namespace glm;

namespace ShushaoEngine {


	Transform::Transform() {

		vector<Transform*> children;

		position = {0.0f, 0.0f, 0.0f};
		localPosition = {0.0f, 0.0f, 0.0f};
		localScale = {1.0f, 1.0f, 1.0f};

		name = "Transform";
	}

	Transform* Transform::getParent() {
		return parent;
	}

	vec3 Transform::getPosition() {
		return position;
	}

	void Transform::setParent(Transform* newpa, bool worldPositionStays) {
		lock = true;
		if (parent != nullptr) {
			parent->RemoveChild(this);
		}

		parent = newpa;

		if (worldPositionStays) {
			localPosition = position - parent->position;
		} else {
			localPosition = {0.0f, 0.0f, 0.0f};
			position = parent->position;
		}

		parent->AddChild(this);
		lock = false;
	}

	void Transform::setParent(Transform* newpa) {
		lock = true;
		Transform::setParent(newpa, false);
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


	void Transform::Awake() {
		// ...
	}

	void Transform::Update() {

		position = (parent != nullptr ? parent->position : vec3(0) ) + localPosition;
		lossyScale = (parent != nullptr ? parent->lossyScale : vec3(1) ) * localScale;

		mat4 Translate = translate(position);
		mat4 Scale = scale(lossyScale);
		mat4 Rotate = rotate(localRotation[0], vec3(localRotation[1], localRotation[2], localRotation[3]));

		//M = Translate * Rotate * Scale;
		M = translate(-pivot) * Translate * translate(pivot) * Rotate * Scale * translate(-pivot);
		MVP = SceneManager::activeScene->activeCamera->Projection * SceneManager::activeScene->activeCamera->getViewMatrix() * M;


	}

}
