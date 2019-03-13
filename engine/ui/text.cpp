
#include "text.h"
#include "../text.h"

namespace ui {

    Text::Text() {
        transform->isRectTransform = true;
        AddComponent<se::Text>();
    }
}
