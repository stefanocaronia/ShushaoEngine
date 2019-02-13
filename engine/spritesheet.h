#pragma once

#include "sprite.h"
#include "textureatlas.h"

namespace se {

	class SpriteSheet : public Object, public vector<Sprite*> {

		public:

			SpriteSheet();
			SpriteSheet(string);
			SpriteSheet(TextureAtlas*);
			SpriteSheet(string, TextureAtlas*);
			~SpriteSheet();

			short cursor = 0;

			Sprite* next();
			Sprite* prev();

			void Add(Sprite*);

			void Load(TextureAtlas*);

		protected:

		private:
	};

}
