#include "canvas.h"
#include "entity.h"
#include "transform.h"

namespace se {

    using namespace std;
    using namespace glm;

	Canvas::Canvas() {
		name = "Canvas";
	}

	Canvas::~Canvas() {}

	Canvas::Canvas(string name_) {
		name = name_;
	}

	void Canvas::ScanChildRenderers() {
		ChildRenderers.clear();
		vector<Component*> components = entity->transform->GetActiveComponentsInChildren();
		for (auto& component : components) {
			if (dynamic_cast<Renderer*>(component)) {
				ChildRenderers.push_back((Renderer*)component);
				((Renderer*)component)->overlay = true;
			}
		}
	}

	void Canvas::Awake() {
		ScanChildRenderers();
	}

	void Canvas::Update() {
		ScanChildRenderers();
	}

    void Canvas::Render() {

	}

	void Canvas::OnDestroy() {

	}

}
