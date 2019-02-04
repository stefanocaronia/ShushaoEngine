#include "maincamera.h"
#include "camera.h"
#include "transform.h"

MainCamera::MainCamera() {

    camera = AddComponent<ShushaoEngine::Camera>();

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

    transform->localPosition = {0.0f, 0.0f, -4.0f};

}

MainCamera::~MainCamera()
{
	//dtor
}
