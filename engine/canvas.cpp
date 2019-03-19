#include "canvas.h"
#include "entity.h"
#include "transform.h"
#include "glmanager.h"
#include "scenemanager.h"

namespace se {

    using namespace std;
    using namespace glm;

	Canvas::~Canvas() {}

	void Canvas::setup() {
		entity->transform->isRectTransform = true;
		entity->canvas = this;
	}

	Canvas* Canvas::SetRenderMode(RenderMode value)	{
		_renderMode = value;
		processRenderMode();
		return this;
	}

	void Canvas::processRenderMode() {
		switch (renderMode) {
			case RenderMode::SCREEN:
				transform->SetPosition({0.0f, 0.0f, 0.0f});
				transform->SetPivot(PivotPosition::BOTTOMLEFT);
				//transform->rectTransform->SetRectSize(GLManager::VIEWPORT);
				transform->rectTransform->SetRect(transform->camera->getRect());
				break;
			case RenderMode::WORLD:
			case RenderMode::CAMERA:
				break;
		}
	}

	void Canvas::Awake() {
		processRenderMode();
	}

	void Canvas::Update() {
		processRenderMode();
	}

    void Canvas::Render() {
	}

	void Canvas::OnDestroy() {
	}

}
