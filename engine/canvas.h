#pragma once

#include "config.h"
#include "renderer.h"
#include "rect.h"
#include "types.h"

namespace se {

	class Canvas : public Component {

		public:

			virtual void setup();
			~Canvas();

			const RenderMode& renderMode = _renderMode;

			std::vector<Component*> ChildRenderers;

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
