
#include "canvas.h"

namespace ui {

    Canvas::Canvas() {
        transform->rectTransform = true;
        canvas = AddComponent<se::Canvas>();
    }
}

