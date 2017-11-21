#pragma once

#include <glm.hpp>

#include "object.h"
#include "rect.h"
#include "texture.h"
#include "config.h"

using namespace glm;
using namespace std;

namespace ShushaoEngine {

	enum class PivotPosition {
		CENTER,
		LEFT,
		RIGHT,
		TOPLEFT,
		TOPRIGHT,
		TOP,
		BOTTOM,
		BOTTOMLEFT,
		BOTTOMRIGHT,
		CUSTOM
	};

	class Sprite : public Object {

		public:

			Sprite();
			Sprite(string);
			Sprite(string, Texture*);
			Sprite(string, Texture*, Rect, PivotPosition, vec2 = vec2(0,0));
			~Sprite();

			Texture* texture = nullptr;

			GLuint vertexBuffer;
			GLuint uvBuffer;
			GLuint indexBuffer;
			GLuint VAO;

			vec2 pivot; // Location of the Sprite's center point in the vertices coordinates

			int pixelPerUnit = Config::pixelPerUnit; // The number of pixels in the sprite that correspond to one unit in world space. (Read Only)

			vec2 textureRectOffset; // Gets the offset of the rectangle this sprite uses on its texture to the original sprite bounds. If sprite mesh type is FullRect, offset is zero.

			GLfloat quad_vertices[12] = {
				-1.0f, -1.0f, 0.0f,  // Bottom-left
				 1.0f, -1.0f, 0.0f, // Bottom-right
				 1.0f,  1.0f, 0.0f, // Top-right
				-1.0f,  1.0f, 0.0f // Top-left
			};

			GLfloat vertices[12] = { // array containing sprite mesh vertex positions.
				-1.0f, -1.0f, 0.0f,  // Bottom-left
				 1.0f, -1.0f, 0.0f, // Bottom-right
				 1.0f,  1.0f, 0.0f, // Top-right
				-1.0f,  1.0f, 0.0f // Top-left
			};

			GLclampd uv[8] = { // The base texture coordinates of the sprite mesh.
				0.0d, 1.0d, // Bottom-left of texture
				1.0d, 1.0d, // Bottom-right of texture
				1.0d, 0.0d, // Top-Right of texture
				0.0d, 0.0d // Top-left of texture
			};

			GLushort indexes[6] = {
				0, 1, 2,
				2, 3, 0
			};

			// metodi

			Sprite* initVAO();
			Sprite* init();

			Rect getRect();
			vec2 getPivot();

			Sprite* setRect(Rect);
			Sprite* setTexture(Texture*);
			Sprite* setPivot(vec2);
			Sprite* setPixelPerUnit(float);

			static vec2 calculatePivot(PivotPosition, Rect, vec2 custom = vec2(0,0));


		protected:

		private:

			Rect rect = Rect::zero; // Location of the Sprite on the original Texture, specified in pixels.
			vec2 pixel_pivot; // Location of the Sprite's center point in the Rect on the original Texture, specified in pixels.


	};

}
