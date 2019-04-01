#pragma once

#include <glm/glm.hpp>
#include <string>
#include <map>

#include "levelmap.h"


#define USER_CONFIG_FILE "config/config.ini"

namespace Config {

	extern std::map<std::string, std::string> data;

	extern void LoadUserConfig();
	extern void LoadEngineConfig();

	extern std::string title;
	extern bool debug;

	// textures
	extern unsigned int pixelPerUnit;

	// display
	extern float displayAspect;
	extern int displayWidth;
	extern int displayHeight;
	extern bool fullscreen;
	extern const std::map<std::string, std::pair<int, int>> DisplayModes;

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

	extern se::LevelMap Layers;
	extern se::LevelMap SortingLayers;
}
