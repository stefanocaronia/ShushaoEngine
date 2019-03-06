#pragma once

#include "entity.h"

namespace se {

	class DebugGrid : public Entity {

		public:
			DebugGrid();

			float gridSize = 1000.0f;
			float gizmoMagnitude = 2.0f;

	};

}
