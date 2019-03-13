#include "canvas.h"
#include "entity.h"
#include "transform.h"
#include "glmanager.h"

namespace se {

    using namespace std;
    using namespace glm;

	Canvas::~Canvas() {}

	void Canvas::setup() {
		entity->transform->isRectTransform = true;
		entity->canvas = this;
		processRenderMode();
	}

	Canvas* Canvas::SetRenderMode(RenderMode value)	{
		_renderMode = value;
		processRenderMode();
		return this;
	}

	void Canvas::processRenderMode() {
		switch (renderMode) {
			case RenderMode::SCREEN:
				//transform->SetPosition({-GLManager::VIEWPORT.x/2, -GLManager::VIEWPORT.y/2, 0.0f});
				transform->SetPosition({0.0f, 0.0f, 0.0f});
				transform->SetPivot(PivotPosition::BOTTOMLEFT);
				transform->rectTransform->SetRectSize({GLManager::VIEWPORT.x, GLManager::VIEWPORT.y});
				break;
			case RenderMode::WORLD:
			case RenderMode::CAMERA:
				break;
		}
	}

	void Canvas::Awake() {
	}

	void Canvas::Update() {
		processRenderMode();
	}

    void Canvas::Render() {
	}

	void Canvas::OnDestroy() {
	}

}
