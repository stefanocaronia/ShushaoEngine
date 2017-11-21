#include "config.h"
#include "utility.h"

namespace Config {

	bool debug 				= true;

	// textures
	int pixelPerUnit 		= 16;

	// display
	float displayAspect 	= 16.0f / 9.0f;
	int displayWidth 		= 1024;
	int displayHeight 		= (int)(displayWidth / displayAspect);
	bool fullscreen 		= false;

	ShushaoEngine::vector_map Layers;
	ShushaoEngine::vector_map SortingLayers;

}
