#include "config.h"

namespace Config {

	bool debug = false;

	// textures
	unsigned int pixelPerUnit = 16;

	// display
	float displayAspect	= 16.0f / 9.0f;
	int displayWidth = 1024;
	int displayHeight = (int)(displayWidth / displayAspect);
	bool fullscreen = false;

	// Time
	namespace Time {
		float fixedRateLimit = 60.0f; // 0.0f -> unlimited
		float frameRateLimit = 0.0f; // 0.0f -> unlimited
	}

	// Physics (Box2d)
	namespace Physics {

		bool enabled = true;
		bool debug = false;
		glm::vec2 gravity = {0, -8.8};
		bool doSleep = true;
		int velocityIterations = 8;
		int positionIterations = 3;

	}

	se::VectorMap Layers;
	se::VectorMap SortingLayers;

}
