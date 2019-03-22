#pragma once

#include <glm/glm.hpp>

#include <GL/glew.h>
#include "renderer.h"
#include "color.h"
#include "material.h"
#include "sprite.h"
#include "shaders/shader.h"

namespace se {

    enum class ImageType {
        SIMPLE, // Displays the full Image
        SLICED, // Displays the Image as a 9-sliced graphic.
        TILED,  // Displays a sliced Sprite with its resizable sections tiled instead of stretched
        FILLED // Displays only a portion of the Image
    };

	class Image : public Renderer {

		public:

			virtual void setup();
			~Image();

			bool isReady();

			Sprite* sprite = nullptr;
			Material* material = nullptr;
			Vao* VAO = nullptr;

			ImageType type = ImageType::SIMPLE;
			glm::vec4 border; // pixel borders for 9-slicing - X=left, Y=bottom, Z=right, W=top

			bool fillCenter = true;
			bool preserveAspect = false;

			Image* SetBorder(glm::vec4 border_) {
				border = border_;
				return this;
			}

			Image* SetFillCenter(bool value_) {
				fillCenter = value_;
				return this;
			}

			Image* SetSprite(Sprite* sprite_) {
				sprite = sprite_;
				return this;
			}

			Image* SetImageType(ImageType type_) {
				type = type_;
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
