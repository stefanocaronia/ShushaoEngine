#pragma once

#include "sprite.h"
#include "textureatlas.h"

namespace ShushaoEngine {

	class SpriteSheet : public Object, public vector<Sprite*> {

		public:

			/*using vector::operator=;
			using vector::assign;
			using vector<Sprite*>;*/

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
