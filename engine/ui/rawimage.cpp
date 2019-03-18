
#include "rawimage.h"
#include "../rawimage.h"

namespace ui {

    RawImage::RawImage() {
        transform->isRectTransform = true;
        AddComponent<se::RawImage>();
    }
}
