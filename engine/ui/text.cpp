
#include "text.h"
#include "../text.h"

namespace se {
namespace ui {

    void Text::Awake() {
        transform->isRectTransform = true;
        AddComponent<se::Text>();
    }
}  // namespace ui
}  // namespace se
