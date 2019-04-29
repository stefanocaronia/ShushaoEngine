#include "debug.h"

namespace se {

// default debug settings

bool Debug::enabled = false;
bool Debug::gridEnabled = true;
bool Debug::infoEnabled = true;
bool Debug::drawTransforms = true;
bool Debug::drawRectTransforms = true;
GridMode Debug::debugGridMode = GridMode::ORTHOGRAFIC;
DebugLevel Debug::level = DebugLevel::INFO;

Logger Debug::Log(Debug::level);

}  // namespace se
