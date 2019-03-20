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

			Sprite* sprite = nullptr;
			Material* material = nullptr;
			Vao* VAO = nullptr;

			bool preserveAspect = false;

			Image* SetSprite(Sprite* sprite_) {
				sprite = sprite_;
				return this;
			}

			Image* SetPreserveAspect(bool value_) {
				preserveAspect = value_;
				return this;
			}

			Image* SetMaterial(Material* material_) {
				material = material_;
				return this;
			}

			Color color = {1.0f, 1.0f, 1.0f, 1.0f}; //	Rendering color for the Sprite graphic.
			bool flipX;//	Flips the sprite on the X axis.
			bool flipY; //	Flips the sprite on the Y axis.

		protected:

			void Awake();
			void Update();
			void Render();
			void OnDestroy();

		private:

			void refreshSprite();
			glm::vec2 last_rectSize;

	};

}
