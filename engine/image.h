#pragma once

#include <glm/glm.hpp>

#include <GL/glew.h>
#include "renderer.h"
#include "color.h"
#include "material.h"
#include "sprite.h"
#include "shaders/shader.h"

namespace se {

	class Image : public Renderer {

		public:

			virtual void setup();
			~Image();

			bool isReady();

			Texture* texture = nullptr;
			Material* material = nullptr;
			Vao* VAO = nullptr;

			Image* SetTexture(Texture* texture_) {
				texture = texture_;
				return this;
			}

			Image* SetMaterial(Material* material_) {
				material = material_;
				return this;
			}

			Image* Build();

			Color color = {1.0f, 1.0f, 1.0f, 1.0f}; //	Rendering color for the Sprite graphic.
			bool flipX;//	Flips the sprite on the X axis.
			bool flipY; //	Flips the sprite on the Y axis.


			std::vector<glm::vec3> vertices {
				{-1.0f, -1.0f, 0.0f},  	// Bottom-left
				{ 1.0f, -1.0f, 0.0f}, 	// Bottom-right
				{ 1.0f,  1.0f, 0.0f}, 	// Top-right
				{-1.0f,  1.0f, 0.0f} 	// Top-left
			};

			std::vector<glm::vec3> normals {
				{ 0.0f,  0.0f, -1.0f}
			};

			std::vector<GLushort> indexes {
				0, 1, 2,
				2, 3, 0
			};

			std::vector<glm::vec2> uv {
				{0.0f, 1.0f}, // Bottom-left of texture
				{1.0f, 1.0f}, // Bottom-right of texture
				{1.0f, 0.0f}, // Top-Right of texture
				{0.0f, 0.0f}	// Top-left of texture
			};

		protected:

			void Awake();
			void Update();
			void Render();
			void OnDestroy();

	};

}
