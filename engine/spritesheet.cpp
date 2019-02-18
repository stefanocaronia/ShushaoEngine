#include "spritesheet.h"
#include "resources.h"
#include "textureatlas.h"
#include "rect.h"
#include "types.h"
#include "utility.h"

namespace se {

	SpriteSheet::SpriteSheet(TextureAtlas* texture) {
		name = "Spritesheet " + texture->name;
		Load(texture);
	}

	SpriteSheet::SpriteSheet(string _name, TextureAtlas* texture) {
		name = _name;
		Load(texture);
	}

	SpriteSheet::SpriteSheet(string _name) {
		name = _name;
	}

	SpriteSheet::~SpriteSheet() {
		// le risorse sono distrutte dal processo madre
		clear();
	}

	Sprite* SpriteSheet::next() {
		if (++cursor >= (int)size()) cursor = 0;
		return (*this)[cursor];
	}

	Sprite* SpriteSheet::prev() {
		if (--cursor < 0) cursor = (int)size() - 1;
		return (*this)[cursor];
	}

	void SpriteSheet::Add(Sprite* sprite) {
		push_back(sprite);
	}

	void SpriteSheet::Load(TextureAtlas* atlas) {

		if (atlas == nullptr) return;

        int counter = 0;

		if (name == "Spritesheet") {
			name = atlas->name;
		}

        if (atlas->slices.size() == 0) {
			return;
        }

        for (const pair<Rect, PivotPosition>& slice : atlas->slices) {
            Rect rect = slice.first;
            PivotPosition pivotpos = slice.second;

			Sprite* sprite = new Sprite(name + "_" + ts(counter), atlas, rect, pivotpos);

			if (sprite != nullptr) {
				Resources::Add(sprite);
				push_back(sprite);
				counter++;
			}
        }
	}

}
