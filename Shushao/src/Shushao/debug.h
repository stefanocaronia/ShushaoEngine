#pragma once

#include "core.h"

#include "logger.h"

namespace se {

enum class GridMode {
    ORTHOGRAFIC,
    PERSPECTIVE
};

class SHUSHAO_API Debug {
public:
    static bool enabled;
    static bool infoEnabled;
    static bool gridEnabled;
    static bool drawTransforms;
    static bool drawRectTransforms;
    static GridMode debugGridMode;
    static DebugLevel level;
    static Logger Log;
};

}  // namespace se
