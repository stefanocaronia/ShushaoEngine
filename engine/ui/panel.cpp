
#include "panel.h"
#include "../image.h"

namespace se {
namespace ui {

    void Panel::Awake() {
        transform->isRectTransform = true;
        AddComponent<se::Image>();
    }
}  // namespace ui
}  // namespace se
