#include "debug.h"

namespace se {

	// default debug settings
	bool Debug::enabled = false;
	bool Debug::gridEnabled = true;
	GridMode Debug::debugGridMode = GridMode::ORTHOGRAFIC;
	DebugLevel Debug::level = DebugLevel::INFO;
	Logger Debug::Log(Debug::level);


}
