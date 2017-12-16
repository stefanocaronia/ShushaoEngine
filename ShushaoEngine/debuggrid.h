#pragma once

#include "entity.h"

namespace ShushaoEngine {

	class DebugGrid : public Entity {

		public:
			DebugGrid();

			float gridSize = 1000.0f;
			float gizmoMagnitude = 4.0f;

	};

}
