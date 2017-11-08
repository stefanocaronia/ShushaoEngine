#include <glm.hpp>
#include <iostream>

#include "camera.h"
#include "libs.h"
#include "transform.h"

using namespace std;
using namespace glm;

namespace ShushaoEngine {

	Camera::Camera() {
		cout << "[" << InstanceID << "] Camera Constructor" << endl;
		name = "Camera";
	}

	mat4 Camera::getProjectionMatrix() {
		if (orthographic) {
			return ortho(-orthographicSize * 2 * aspect, orthographicSize * 2 * aspect, -orthographicSize * 2, orthographicSize * 2, nearClipPlane, farClipPlane);
		} else {
			return perspective(fieldOfView, aspect, nearClipPlane, farClipPlane);
		}
	}

	mat4 Camera::getViewMatrix() {
		return glm::lookAt(transform->position, transform->forward, transform->up);
	}
}
