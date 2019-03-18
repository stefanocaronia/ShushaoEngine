
#include "image.h"
#include "../image.h"

namespace ui {

    Image::Image() {
        transform->isRectTransform = true;
        AddComponent<se::Image>();
    }
}
