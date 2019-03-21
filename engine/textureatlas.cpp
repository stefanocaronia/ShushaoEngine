#include <glm/glm.hpp>

#include "textureatlas.h"
#include "debug.h"
#include "globals.h"

namespace se {

	using namespace std;
	using namespace glm;

	void TextureAtlas::AddSlice(Rect _rect, Align _Align) {
		if (TextureID == 0) {
			Debug::Log(WARNING, SOURCE) << "No texture loaded" << endl;
			return;
		}
		slices.push_back({_rect, _Align});
	}

	void TextureAtlas::AddGrid(vec2 _size, Align _pivotPos, vec2 _offset, vec2 _padding) {

		if (TextureID == 0) {
			Debug::Log(WARNING, SOURCE) << "No texture loaded" << endl;
			return;
		}

		vec2 cursor = vec2(0, 0) + _offset;
		vec2 step = _size + _padding;

		while(cursor.y < height) {
			while (cursor.x < width) {
				Rect slice;
				slice.Set(cursor.x + _padding.x, cursor.y + _padding.y, _size.x, _size.y);
				AddSlice(slice, _pivotPos);
				cursor.x += step.x;
			}
			cursor.y += step.y;
		}
	}
}
