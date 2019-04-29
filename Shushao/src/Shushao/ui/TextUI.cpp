
#include "TextUI.h"
#include "../text.h"

namespace se {
namespace ui {

    void TextUI::Awake() {
        transform->isRectTransform = true;
        AddComponent<se::Text>();
    }
}  // namespace ui
}  // namespace se
