#pragma once

namespace se {

    enum class Align {
        CENTER,
        LEFT,
        RIGHT,
        TOPLEFT,
        TOPRIGHT,
        TOP,
        BOTTOM,
        BOTTOMLEFT,
        BOTTOMRIGHT,
        CUSTOM
    };

	namespace PivotPosition {
		const glm::vec2 CENTER 		= {0.5f, 0.5f};
		const glm::vec2 LEFT 		= {0.0f, 0.5f};
		const glm::vec2 RIGHT 		= {1.0f, 0.5f};
		const glm::vec2 TOPLEFT 	= {0.0f, 1.0f};
		const glm::vec2 TOPRIGHT 	= {1.0f, 1.0f};
		const glm::vec2 TOP 		= {0.5f, 1.0f};
		const glm::vec2 BOTTOM 		= {0.5f, 0.0f};
		const glm::vec2 BOTTOMLEFT 	= {0.0f, 0.0f};
		const glm::vec2 BOTTOMRIGHT = {1.0f, 0.0f};
	};

	enum class RenderMode {
		WORLD,
		SCREEN,
		CAMERA
	};
}
