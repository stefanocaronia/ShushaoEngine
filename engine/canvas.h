#pragma once

#include "config.h"
#include "renderer.h"
#include "rect.h"
#include "globals.h"
#include "camera.h"

namespace se {

	class Canvas : public Component {

		public:

			virtual void setup();
			~Canvas();

			const RenderMode& renderMode = _renderMode;
			Camera* camera = nullptr;

			std::vector<Component*> ChildRenderers;

			Canvas* SetRenderMode(RenderMode value);
			Canvas* SetCamera(Camera* camera_);

			void Awake();
			void Update();
			void Render();
			void OnDestroy();

			void Copy(Canvas* other);

        private:

			RenderMode _renderMode = RenderMode::WORLD;
			RenderMode _lastRenderMode;
			void processRenderMode();

	};

}
