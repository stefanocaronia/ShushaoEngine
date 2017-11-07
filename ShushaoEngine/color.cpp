#include "color.h"

#include <string>

using namespace std;

namespace ShushaoEngine {

	Color::Color() {
		r = 0.0f;
		g = 0.0f;
		b = 0.0f;
		a = 1.0f;
	}

	Color::Color(float _r, float _g, float _b, float _a) {
		r = _r;
		g = _g;
		b = _b;
		a = _a;
	}

}
