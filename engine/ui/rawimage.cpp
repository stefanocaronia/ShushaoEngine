
#include "rawimage.h"
#include "../rawimage.h"

namespace se {
namespace ui {

    void RawImage::Awake() {
        transform->isRectTransform = true;
        AddComponent<se::RawImage>();
    }
}  // namespace ui
}  // namespace se
