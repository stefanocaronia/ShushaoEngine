#include "debug.h"

namespace ShushaoEngine {

	// default debug settings
	bool Debug::enabled = true;
	bool Debug::gridEnabled = true;
	GridMode Debug::debugGridMode = GridMode::ORTHOGRAFIC;
	DebugLevel Debug::level = DebugLevel::INFO;
	Logger Debug::Log(Debug::level);


}
