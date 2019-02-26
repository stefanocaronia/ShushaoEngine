#include "color.h"
#include "utility.h"

namespace se {

	Color::Color() {
		r = 0.0f;
		g = 0.0f;
		b = 0.0f;
		a = 1.0f;

		rgba = {r, g, b, a};
	}

	Color::Color(float r_, float g_, float b_, float a_) {
		r = r_;
		g = g_;
		b = b_;
		a = a_;

		rgba = {r, g, b, a};
	}

	float Color::maxColorComponent() {
		return max(max(r, g), b);
	}

	string Color::ToString() {
		return "("+ts(r)+","+ts(g)+","+ts(b)+","+ts(a)+")";
	}

	Color Color::black = {0.0f, 0.0f, 0.0f, 1.0f};
	Color Color::blue = {0.0f, 0.0f, 1.0f, 1.0f};
	Color Color::clear = {0.0f, 0.0f, 0.0f, 0.0f};
	Color Color::cyan = {0.0f, 1.0f, 1.0f, 1.0f};
	Color Color::gray = {0.5f, 0.5f, 0.5f, 1.0f};
	Color Color::green = {0.0f, 1.0f, 0.0f, 1.0f};
	Color Color::grey = {0.5f, 0.5f, 0.5f, 1.0f};
	Color Color::magenta = {1.0f, 0.0f, 1.0f, 1.0f};
	Color Color::red = {1.0f, 0.0f, 0.0f, 1.0f};
	Color Color::white = {1.0f, 1.0f, 1.0f, 1.0f};
	Color Color::yellow = {1.0f, 0.92f, 0.016f, 1.0f};

}
