#include <glm/glm.hpp>
#include <iostream>

#include "config.h"
#include "debug.h"
#include "camera.h"
#include "gllibs.h"
#include "transform.h"

using namespace std;
using namespace glm;

namespace ShushaoEngine {

	Camera::Camera() {
		name = "Camera";

		aspect = (float)Config::displayWidth / (float)Config::displayHeight;

		Projection = getProjectionMatrix();
	}

	mat4 Camera::getProjectionMatrix() {

		aspect = (float)Config::displayWidth / (float)Config::displayHeight;
		if (orthographic) {
			return ortho(
				-orthographicSize * aspect,
				orthographicSize * aspect,
				-orthographicSize,
				orthographicSize,
				nearClipPlane,
				farClipPlane
			);
		} else {
			return perspective(fieldOfView, aspect, nearClipPlane, farClipPlane);
		}
	}

	mat4 Camera::getViewMatrix() {
		return lookAt(transform->localPosition, Transform::FORWARD, Transform::UP);
	}

	float Camera::getDepth() {
		return depth;
	}

	bool Camera::getOrthographic() {
		return orthographic;
	}

	float Camera::getOrthographicSize() {
		return orthographicSize;
	}

	float Camera::getFieldOfView() {
		return fieldOfView;
	}

	float Camera::getFarClipPlane() {
		return farClipPlane;
	}

	float Camera::getNearClipPlane() {
		return nearClipPlane;
	}

	Rect Camera::getRect() {
		return rect;
	}

	void Camera::setDepth(float value) {
		depth = value;
		Projection = getProjectionMatrix();
	}

	void Camera::setOrthographic(bool value) {
		orthographic = value;
		Projection = getProjectionMatrix();
	}

	void Camera::setOrthographicSize(float value) {
		orthographicSize = value;
		Projection = getProjectionMatrix();
	}

	void Camera::setFieldOfView(float value) {
		fieldOfView = value;
		Projection = getProjectionMatrix();
	}

	void Camera::setFarClipPlane(float value) {
		farClipPlane = value;
		Projection = getProjectionMatrix();
	}

	void Camera::setNearClipPlane(float value) {
		nearClipPlane = value;
		Projection = getProjectionMatrix();
	}

	void Camera::setRect(Rect value) {
		rect = value;
		Projection = getProjectionMatrix();
	}

	void Camera::print() {
		Logger::setColor(ConsoleColor::CYAN);

		cout << " Camera " << name << endl;

		cout << "  - " << "backgroundColor: " << backgroundColor.r << " " << backgroundColor.g << " " << backgroundColor.b << " " << backgroundColor.a << endl;
		cout << "  - " << "aspect: " << aspect << endl;
		cout << "  - " << "orthographic: " << (orthographic?"true":"false") << endl;
		cout << "  - " << "orthographicSize: " << orthographicSize << endl;
		cout << "  - " << "depth: " << depth << endl;
		cout << "  - " << "fieldOfView: " << fieldOfView << endl;
		cout << "  - " << "farClipPlane: " << farClipPlane << endl;
		cout << "  - " << "nearClipPlane: " << nearClipPlane << endl;
		cout << "  - " << "rect: " << rect.x << " " << rect.y << " " << rect.width << " " << rect.height << endl;

		Logger::setColor(ConsoleColor::LIGHTGREY);
	}
}
