#pragma once

#include <glm.hpp>

#include "renderer.h"
#include "sprite.h"
#include "color.h"
#include "shader.h"

namespace ShushaoEngine {

	enum SpriteDrawMode {
		Simple,
		Sliced,
		Tiled
	};

	enum SpriteTileMode {
		Continuous,
		Adaptive
	};

	class SpriteRenderer : public Renderer {

		public:

			SpriteRenderer();
			SpriteRenderer(string);

			bool isReady();

			//float adaptiveModeThreshold; //	The current threshold for Sprite Renderer tiling.
			Color color = {1.0f, 1.0f, 1.0f, 1.0f}; //	Rendering color for the Sprite graphic.
			//SpriteDrawMode drawMode; //	The current draw mode of the Sprite Renderer.
			bool flipX;//	Flips the sprite on the X axis.
			bool flipY; //	Flips the sprite on the Y axis.
			// maskInteraction //	Specifies how the sprite interacts with the masks.
			vec2 size; //	Property to set/get the size to render when the SpriteRenderer.drawMode is set to SpriteDrawMode.NineSlice.

			//SpriteTileMode tileMode; //	The current tile mode of the Sprite Renderer.

			// GLuint vertexBuffer;
			// GLuint uvBuffer;
			// GLuint indexBuffer;
			// GLuint VAO;

			Sprite* sprite = nullptr;
			Shader* shader = nullptr;;

			void Awake();
			void Update();
			void Render();
			void OnDestroy();
	};

}
