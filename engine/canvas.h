#pragma once

#include "config.h"
#include "renderer.h"
#include "rect.h"

namespace se {

	enum class RenderMode {
		WORLD,
		OVERLAY
	};

	class Canvas : public Component {

		public:

			Canvas();
			Canvas(std::string);
			~Canvas();

			const RenderMode& renderMode = _renderMode;

			std::vector<Component*> ChildRenderers;

			void ScanChildRenderers();

			Canvas* SetRenderMode(RenderMode value)	{ _renderMode = value; return this;}

			void Awake();
			void Update();
			void Render();
			void OnDestroy();

        private:

            Rect _rect;
			RenderMode _renderMode = RenderMode::WORLD;

	};

}
