#include "maincamera.h"
#include "../camera.h"
#include "../transform.h"

namespace se {
void MainCamera::Awake() {
    camera = AddComponent<se::Camera>();

    tag = "Main Camera";
    name = "Main Camera";

    camera->enabled = true;
    camera->backgroundColor = {0.0f, 0.0f, 0.0f, 1.0f};
    transform->localPosition = {0.0f, 0.0f, 10.0f};
}
}  // namespace se
