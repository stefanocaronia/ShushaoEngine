#pragma once

#include <map>
#include <string>
#include <vector>
#include <algorithm>

#include "utility.h"

using namespace std;

namespace Config {

	extern bool debug;

	extern int pixelPerUnit;

	extern float displayAspect;
	extern int displayWidth;
	extern int displayHeight;
	extern bool fullscreen;

	extern ShushaoEngine::vector_map Layers;
	extern ShushaoEngine::vector_map SortingLayers;
}
