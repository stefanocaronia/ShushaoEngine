
#include "ImageUI.h"
#include "../image.h"

namespace se {
namespace ui {

    void ImageUI::Awake() {
        transform->isRectTransform = true;
        AddComponent<se::Image>();
    }
}  // namespace ui
}  // namespace se
