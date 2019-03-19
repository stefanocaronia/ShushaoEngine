#include <string>
#include <glm/glm.hpp>

#include "color.h"
#include "utility.h"

namespace se {

	Color::Color() {
		Set(0.0f, 0.0f, 0.0f, 1.0f);
	}

	Color::Color(float r_, float g_, float b_, float a_) {
		Set(r_, g_, b_, a_);
	}

	Color::Color(std::string hexcode) {
		glm::vec3 col = hex2rgb(hexcode);
		Set(col.r, col.g, col.b, 1.0f);
	}

	void Color::Set(float r_, float g_, float b_, float a_) {
		r = r_;
		g = g_;
		b = b_;
		a = a_;
	}

	glm::vec4 Color::rgba() {
		return {r, g, b, a};
	}

	glm::vec3 Color::rgb() {
		return {r, g, b};
	}

	float Color::maxColorComponent() {
		return max(max(r, g), b);
	}

	glm::vec3 Color::hex2rgb(string hexcode) {

		hexcode.erase(std::remove(hexcode.begin(), hexcode.end(), '#'), hexcode.end());

		int hexValue = stoi(hexcode, 0, 16);

		glm::vec3 rgbColor;
		rgbColor.r = ((hexValue >> 16) & 0xFF) / 255.0;  // Extract the RR byte
		rgbColor.g = ((hexValue >> 8) & 0xFF) / 255.0;   // Extract the GG byte
		rgbColor.b = ((hexValue) & 0xFF) / 255.0;        // Extract the BB byte

		return rgbColor;
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
