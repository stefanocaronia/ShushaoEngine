#pragma once

#include <vector>

#include "texture.h"
#include "rect.h"
#include "sprite.h"
#include "types.h"

namespace se {

	class TextureAtlas : public Texture {

		public:

			TextureAtlas() {};
			TextureAtlas(std::string filename) : Texture(filename) {};
			TextureAtlas(std::string filename, std::string n) : Texture(filename, n) {};

			vector<pair<Rect, Align>> slices;

			void AddSlice(Rect, Align pp = Align::CENTER);

            void AddGrid(
				glm::vec2,
				Align pp = Align::CENTER,
				glm::vec2 = glm::vec2(0,0),
				glm::vec2 = glm::vec2(0,0)
			);

	};

}
