#pragma once

#include <glm.hpp>

#include "object.h"
#include "rect.h"
#include "texture.h"
#include "config.h"

using namespace glm;
using namespace std;

namespace ShushaoEngine {

	class Sprite : public Object {

		public:

			Sprite();
			Sprite(string);
			Sprite(Texture*);
			Sprite(Texture*, Rect, vec2);

			~Sprite();

			//vec4 border; // TODO

			// Bounds bounds // TODO
			int pixelPerUnit = Config::pixelPerUnit; // The number of pixels in the sprite that correspond to one unit in world space. (Read Only)
			Rect rect = Rect::zero; // Location of the Sprite on the original Texture, specified in pixels.
			vec2 pivot; // Location of the Sprite's center point in the Rect on the original Texture, specified in pixels.
			Texture* texture; // Get the reference to the used texture. If packed this will point to the atlas, if not packed will point to the source sprite.
			vec2 textureRectOffset; // Gets the offset of the rectangle this sprite uses on its texture to the original sprite bounds. If sprite mesh type is FullRect, offset is zero.

			GLfloat vertices[12] = { // array containing sprite mesh vertex positions.
				-1.0f, -1.0f, 0.0f,  // Bottom-left
				 1.0f, -1.0f, 0.0f, // Bottom-right
				 1.0f,  1.0f, 0.0f, // Top-right
				-1.0f,  1.0f, 0.0f // Top-left
			};

			GLfloat uv[8] = { // The base texture coordinates of the sprite mesh.
				1.0f, 1.0f, // Bottom-right of texture
				0.0f, 1.0f, // Top-right of texture
				0.0f, 0.0f, // Top-left of texture
				1.0f, 0.0f // Bottom-left of texture
			};

			GLuint indexes[6] = {
				0, 1, 2,
				2, 3, 0
			};

			GLuint vertexBuffer;
			GLuint uvBuffer;
			GLuint indexBuffer;
			GLuint VAO;

			vector<vec3> getVertices();
			vector<vec2> getUV();

			//static Sprite* Create(Texture*, Rect, vec2);

			// metodi

			void updateVertices();

			void initVAO();

		protected:

		private:
	};

}
