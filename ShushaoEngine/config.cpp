#include "config.h"

namespace Config {

	// textures
	int pixelPerUnit 		= 16;

	// display
	float displayAspect 	= 16.0f / 9.0f;
	int displayWidth 		= 1024;
	int displayHeight 		= (int)(displayWidth / displayAspect);
	bool Fullscreen 		= false;

}
