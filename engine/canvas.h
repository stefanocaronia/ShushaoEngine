#pragma once

#include "config.h"
#include "renderer.h"
#include "rect.h"

namespace se {

	enum class RenderMode {
		WORLD,
		SCREEN,
		CAMERA
	};

	class Canvas : public Component {

		public:

			virtual void setup();
			~Canvas();

			const RenderMode& renderMode = _renderMode;

			std::vector<Component*> ChildRenderers;

			// void ScanChildRenderers();

			Canvas* SetRenderMode(RenderMode value);

			void Awake();
			void Update();
			void Render();
			void OnDestroy();

        private:

			RenderMode _renderMode = RenderMode::WORLD;
			void processRenderMode();

	};

}
