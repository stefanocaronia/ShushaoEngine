#pragma once

#include "entity.h"
#include "color.h"
#include "debug.h"

using namespace std;
using namespace glm;

namespace ShushaoEngine {

	class DebugGrid : public Entity {

		public:
			DebugGrid();

			float gridSize = 1000.0f;
			float gizmoMagnitude = 4.0f;

	};

}
