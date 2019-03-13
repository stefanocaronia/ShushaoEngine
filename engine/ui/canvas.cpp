
#include "canvas.h"

namespace ui {

    Canvas::Canvas() {
        transform->isRectTransform = true;
        canvas = AddComponent<se::Canvas>();
    }
}

