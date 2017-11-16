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

	Transform* Transform::GetParent() {
		return parent;
	}

	void Transform::SetParent(Transform* newpa, bool worldPositionStays) {
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
	}

	void Transform::SetParent(Transform* newpa) {
		Transform::SetParent(newpa, false);
	}

	void Transform::RemoveChild(Transform* t) {
		if (children.empty()) return;
		vector<Transform*>::iterator position = find(children.begin(), children.end(), t);
		if (position != children.end()) children.erase(position);
	}

	void Transform::AddChild(Transform* t) {
		if (children.empty()) {
			children.push_back(t);
			return;
		}
		vector<Transform*>::iterator position = find(children.begin(), children.end(), t);
		if (position == children.end()) children.push_back(t);
	}


	void Transform::init() {
		// ...
	}

	void Transform::update() {

		Camera* camera = SceneManager::activeScene->activeCamera;
		SpriteRenderer* sr = entity->GetComponent<SpriteRenderer>();
		vec3 pivot = (sr != nullptr && sr->isReady() ? vec3(sr->sprite->pivot, 0.0f) : vec3(0.0f, 0.0f, 0.0f));

		mat4 ParentTranslate = (parent != nullptr ? translate(parent->position) : mat4());
		mat4 Translate = ParentTranslate * translate(localPosition);
		mat4 Scale = scale(localScale);
		mat4 Rotate = rotate(localRotation[0], vec3(localRotation[1], localRotation[2], localRotation[3]));

		//M = Translate * Rotate * Scale;
		M = translate(-pivot) * Translate * translate(pivot) * Rotate * Scale * translate(-pivot);
		MVP = camera->Projection * camera->getViewMatrix() * M;

	}

	void Transform::render() {
		// to implement in derived classes
	}

	void Transform::fixed() {
		// to implement in derived classes
	}

}
