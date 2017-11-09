#pragma once

#include <map>
#include <string>

using namespace std;

namespace Config {

	extern bool debug;

	extern int pixelPerUnit;

	extern float displayAspect;
	extern int displayWidth;
	extern int displayHeight;
	extern bool Fullscreen;

	extern map<int, string> Layers;
	extern map<int, string> SortingLayers;


}
