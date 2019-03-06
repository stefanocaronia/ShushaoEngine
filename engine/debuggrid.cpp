#include "debuggrid.h"

#include "color.h"
#include "debug.h"
#include "linerenderer.h"

namespace se {

	DebugGrid::DebugGrid() {

		LineRenderer* LR = AddComponent<LineRenderer>();
		LR->sortingLayerID = Config::SortingLayers.over();

		Color xcol = {0.0f, 1.0f, 0.0f, 0.5f};
		Color ycol = {1.0f, 0.0f, 0.0f, 0.5f};
		Color zcol = {0.0f, 0.0f, 1.0f, 0.5f};
		Color gcol = {0.5f, 0.5f, 0.5f, 0.1f};

		Color gco = gcol;
		float alpha = 0.2f;
		for (float i = 0.0f; i < gridSize; i++) {

			alpha -= 0.005f;

			if (fmod(i, 10.0f) == 0) gco.a = alpha * 3; else gco.a = alpha;

			if (Debug::debugGridMode == GridMode::ORTHOGRAFIC) {
				// parallele asse Y lungo X
				LR->AddLine({i, -gridSize, 0.0f}, {i, gridSize, 0.0f}, gco);
				LR->AddLine({-i, -gridSize, 0.0f}, {-i, gridSize, 0.0f}, gco);

				// parallele asse X lungo Y
				LR->AddLine({-gridSize, i, 0.0f}, {gridSize, i, 0.0f}, gco);
				LR->AddLine({-gridSize, -i, 0.0f}, {gridSize, -i, 0.0f}, gco);
			} else {
				//parallele asse X lungo Z
				LR->AddLine({-gridSize, 0.0f, i}, {gridSize, 0.0f, i}, gco);
				LR->AddLine({-gridSize, 0.0f, -i}, {gridSize, 0.0f, -i}, gco);

				//parallele asse Z lungo X
				LR->AddLine({i, 0.0f, -gridSize}, {i, 0.0f, gridSize}, gco);
				LR->AddLine({-i, 0.0f, -gridSize}, {-i, 0.0f, gridSize}, gco);
			}
		}

		float arrowWidth = gizmoMagnitude / 18;

		LR->AddLine({0.0f, 0.0f, 0.0f},	{0.0f, gizmoMagnitude, 0.0f}, xcol);
		LR->AddLine({0.0f, 0.0f, 0.0f},	{gizmoMagnitude, 0.0f, 0.0f}, ycol);
		LR->AddLine({0.0f, 0.0f, 0.0f},	{0.0f, 0.0f, gizmoMagnitude}, zcol);

		LR->AddLine({0.0f, gizmoMagnitude, 0.0f}, {arrowWidth, gizmoMagnitude - arrowWidth, 0.0f}, xcol);
		LR->AddLine({0.0f, gizmoMagnitude, 0.0f}, {-arrowWidth, gizmoMagnitude - arrowWidth, 0.0f}, xcol);

		LR->AddLine({gizmoMagnitude, 0.0f, 0.0f}, {gizmoMagnitude - arrowWidth, arrowWidth, 0.0f}, ycol);
		LR->AddLine({gizmoMagnitude, 0.0f, 0.0f}, {gizmoMagnitude - arrowWidth, -arrowWidth, 0.0f}, ycol);

		if (Debug::debugGridMode == GridMode::PERSPECTIVE) {
			LR->AddLine({0.0f, 0.0f, gizmoMagnitude}, {arrowWidth, 0.0f, gizmoMagnitude - arrowWidth}, zcol);
			LR->AddLine({0.0f, 0.0f, gizmoMagnitude}, {-arrowWidth, 0.0f, gizmoMagnitude - arrowWidth}, zcol);
		}

	}

}
