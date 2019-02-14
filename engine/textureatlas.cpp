#include <glm/glm.hpp>

#include "textureatlas.h"
#include "debug.h"

using namespace std;

namespace se {

	void TextureAtlas::AddSlice(Rect _rect, PivotPosition _pivotPosition) {
		if (TextureID == 0) {
			Debug::Log(WARNING, SOURCE) << "No texture loaded" << endl;
			return;
		}
		slices.push_back({_rect, _pivotPosition});
	}

	void TextureAtlas::AddGrid(vec2 _size, PivotPosition _pivotPos, vec2 _offset, vec2 _padding) {

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
