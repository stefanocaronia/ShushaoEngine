#include "spritesheet.h"
#include "resources.h"


namespace ShushaoEngine {

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

	void SpriteSheet::Load(TextureAtlas* texture) {

		if (name == "Spritesheet") name = texture->name;

        int counter = 0;

        for (auto it = texture->slices.begin(); it != texture->slices.end(); it++) {
            Rect rect = it->first;
            PivotPosition pivotpos = it->second;

			Sprite* sprite = new Sprite(name + "_" + ts(counter), texture, rect, pivotpos);

			if (sprite != nullptr) {
				Resources::Add(sprite);
				push_back(sprite);
				counter++;
			}
        }
	}

}
