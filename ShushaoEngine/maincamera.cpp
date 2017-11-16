#include "maincamera.h"

using namespace ShushaoEngine;

using namespace glm;

MainCamera::MainCamera() {

    camera = AddComponent<Camera>();
    tag = "Main Camera";
    name = "Main Camera";

    camera->enabled = true;
    camera->backgroundColor = {0.0f, 0.0f, 0.0f, 1.0f};
    /*camera->orthographic = true;
    camera->fieldOfView = 45.0f;
    camera->nearClipPlane = 0.1f;
    camera->farClipPlane = 100.0;
    camera->aspect = 16.0f / 9.0f;
    camera->orthographicSize = 5.0f;
    camera->rect = {0.0f, 0.0f, 1.0f, 1.0f};*/

    transform->localPosition = vec3(0.0f, 0.0f, -4.0f);
	transform->localRotation = quat(0.0f, 0.0f, 0.0f, 0.0f);
	transform->up = vec3(0.0f, 1.0f, 0.0f);

}

MainCamera::~MainCamera()
{
	//dtor
}
