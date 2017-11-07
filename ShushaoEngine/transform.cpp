#include "transform.h"

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

namespace ShushaoEngine {

	Transform::Transform() {

		position = {0.0f, 0.0f, 0.0f};
		localPosition = {0.0f, 0.0f, 0.0f};
		localScale = {1.0f, 1.0f, 1.0f};

		cout << "[" << InstanceID << "] Transform Constructor" << endl;
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
		vector<Transform*>::iterator position = find(begin(), end(), t);
		if (position != end()) erase(position);
	}

	void Transform::AddChild(Transform* t) {
		vector<Transform*>::iterator position = find(begin(), end(), t);
		if (position == end()) push_back(t);
	}




	void Transform::updateCycle() {

		glm::mat4 Translate = glm::translate(position);
		glm::mat4 Scale = glm::scale(lossyScale);
		glm::mat4 Rotate = glm::rotate(rotation[0],glm::vec3(rotation[1],rotation[2],rotation[3]));

		M = Translate * Rotate * Scale;
		MVP = GL.Projection * GL.View * M;
	}

	void Transform::renderCycle() {
		// to implement in derived classes
	}

	void Transform::fixedUpdateCycle() {
		// to implement in derived classes
	}

}
