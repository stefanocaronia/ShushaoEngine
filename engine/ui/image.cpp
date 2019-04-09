
#include "image.h"
#include "../image.h"

namespace se {
namespace ui {

    void Image::Awake() {
        transform->isRectTransform = true;
        AddComponent<se::Image>();
    }
}  // namespace ui
}  // namespace se
