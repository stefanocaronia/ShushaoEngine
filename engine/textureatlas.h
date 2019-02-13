#pragma once

#include <vector>

#include "texture.h"
#include "rect.h"
#include "sprite.h"

namespace se {

	using namespace std;

	class TextureAtlas : public Texture {

		public:

			TextureAtlas() {};
			TextureAtlas(string filename) : Texture(filename) {};
			TextureAtlas(string filename, string n) : Texture(filename, n) {};

			vector<pair<Rect, PivotPosition>> slices;
			void AddSlice(Rect, PivotPosition pp = PivotPosition::CENTER);
            void AddGrid(vec2, PivotPosition pp = PivotPosition::CENTER, vec2 = vec2(0,0), vec2 = vec2(0,0));

	};

}
