
#include "RawImageUI.h"
#include "../rawimage.h"

namespace se {
namespace ui {

    void RawImageUI::Awake() {
        transform->isRectTransform = true;
        AddComponent<se::RawImage>();
    }
}  // namespace ui
}  // namespace se
