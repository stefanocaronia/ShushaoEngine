#pragma once

#include <glm/glm.hpp>

#define _USE_MATH_DEFINES

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

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
	}

	struct AnchorPoints {
		glm::vec2 min;
		glm::vec2 max;
	};

	namespace AnchorPreset { //     		       MIN		     MAX
		const AnchorPoints TOPLEFT 			= {{0.0f, 1.0f}, {0.0f, 1.0f}};
		const AnchorPoints TOP 				= {{0.5f, 1.0f}, {0.5f, 1.0f}};
		const AnchorPoints TOPRIGHT			= {{1.0f, 1.0f}, {1.0f, 1.0f}};
		const AnchorPoints TOPSTRETCH 		= {{0.0f, 1.0f}, {1.0f, 1.0f}};

		const AnchorPoints LEFT 			= {{0.0f, 0.5f}, {0.0f, 0.5f}};
		const AnchorPoints CENTER 			= {{0.5f, 0.5f}, {0.5f, 0.5f}};
		const AnchorPoints RIGHT 			= {{1.0f, 0.5f}, {1.0f, 0.5f}};
		const AnchorPoints MIDDLESTRETCH 	= {{0.0f, 0.5f}, {1.0f, 0.5f}};

		const AnchorPoints BOTTOMLEFT 		= {{0.0f, 0.0f}, {0.0f, 0.0f}};
		const AnchorPoints BOTTOM 			= {{0.5f, 0.0f}, {0.5f, 0.0f}};
		const AnchorPoints BOTTOMRIGHT 		= {{1.0f, 0.0f}, {1.0f, 0.0f}};
		const AnchorPoints BOTTOMSTRETCH 	= {{0.0f, 0.0f}, {1.0f, 0.0f}};

		const AnchorPoints STRETCH 			= {{0.0f, 0.0f}, {1.0f, 1.0f}};
	}

	enum class RenderMode {
		WORLD,
		SCREEN,
		CAMERA
	};
}
