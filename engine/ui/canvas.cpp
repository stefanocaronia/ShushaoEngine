
#include "canvas.h"

namespace se {
namespace ui {

    void Canvas::Awake() {
        transform->isRectTransform = true;
        canvas = AddComponent<se::Canvas>();
    }
}  // namespace ui
}  // namespace se
