
#include "panel.h"
#include "../image.h"

namespace ui {

    Panel::Panel() {
        transform->isRectTransform = true;
        AddComponent<se::Image>();
    }
}
