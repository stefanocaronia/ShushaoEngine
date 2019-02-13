#pragma once

#include <glm/glm.hpp>

#include "utility.h"

namespace se {
    class VectorMap;
}

namespace Config {

	extern bool debug;

	// textures
	extern int pixelPerUnit;

	// display
	extern float displayAspect;
	extern int displayWidth;
	extern int displayHeight;
	extern bool fullscreen;

	// time
	namespace Time {
		extern float fixedRateLimit; // 0.0f -> unlimited
		extern float frameRateLimit; // 0.0f -> unlimited
	}

	// Physics (box2d)
	namespace Physics {
		extern bool enabled;
		extern bool debug;
		extern glm::vec2 gravity;
		extern bool doSleep;
		extern int velocityIterations;
		extern int positionIterations;
	}

	extern se::VectorMap Layers;
	extern se::VectorMap SortingLayers;
}
