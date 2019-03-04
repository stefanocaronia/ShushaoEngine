#pragma once

#include <glm/glm.hpp>
#include "object.h"
#include "rect.h"
#include "texture.h"
#include "config.h"
#include "types.h"
#include "vao.h"

namespace se {

	class Sprite : public Object {

		public:

			Sprite();
			Sprite(std::string name_);
			Sprite(std::string name_, Texture* texture_);
			~Sprite();

			Texture* texture = nullptr;
			Vao* VAO = nullptr;

			bool ready = false;
			glm::vec2 pivot; // Location of the Sprite's center point in the vertices coordinates
			unsigned int pixelPerUnit = Config::pixelPerUnit; // The number of pixels in the sprite that correspond to one unit in world space. (Read Only)
			glm::vec2 textureRectOffset; // Gets the offset of the rectangle this sprite uses on its texture to the original sprite bounds. If sprite mesh type is FullRect, offset is zero.

			std::vector<glm::vec3> vertices {
				{-1.0f, -1.0f, 0.0f},  	// Bottom-left
				{ 1.0f, -1.0f, 0.0f}, 	// Bottom-right
				{ 1.0f,  1.0f, 0.0f}, 	// Top-right
				{-1.0f,  1.0f, 0.0f} 	// Top-left
			};

			std::vector<GLushort> indexes {
				0, 1, 2,
				2, 3, 0
			};

			std::vector<GLclampd> uv {
				0.0f, 1.0f, // Bottom-left of texture
				1.0f, 1.0f, // Bottom-right of texture
				1.0f, 0.0f, // Top-Right of texture
				0.0f, 0.0f 	// Top-left of texture
			};

			// metodi
			Sprite* Init();
			Sprite* Build();
			Rect GetRect();
			glm::vec2 GetPivot();

			Sprite* SetRect(Rect);
			Sprite* SetTexture(Texture*);
			Sprite* SetPivot(PivotPosition);
			Sprite* SetPivot(vec2);
			Sprite* SetPixelPerUnit(unsigned int);

			static glm::vec2 CalculatePivot(PivotPosition, Rect, vec2 custom = vec2(0,0));

		protected:

		private:

			Rect rect = Rect::zero; // Location of the Sprite on the original Texture, specified in pixels.
			glm::vec2 pixel_pivot; // Location of the Sprite's center point in the Rect on the original Texture, specified in pixels.

	};

}
