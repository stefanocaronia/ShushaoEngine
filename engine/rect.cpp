#include <iostream>
#include <sstream>

#include "rect.h"

namespace se {

	using namespace glm;
	using namespace std;

	Rect::Rect() {

		Set(0.0f, 0.0f, 0.0f, 0.0f);
	}

	Rect::Rect(float _x, float _y, float _w, float _h) {

		Set(_x, _y, _w, _h);
	}

	string Rect::ToString() {

		std::ostringstream stream;

		stream << "\n*** Rect Info Dump ***" << "\n\n";

		stream << " - x \t\t= " << x << "\n";
		stream << " - y \t\t= " << y << "\n";
		stream << " - width \t= " << width << "\n";
		stream << " - height \t= " << height << "\n";
		stream << " - xMin \t= " << xMin << "\n";
		stream << " - xMax \t= " << xMax << "\n";
		stream << " - yMin \t= " << yMin << "\n";
		stream << " - yMax \t= " << yMax << "\n";
		stream << " - center \t= " << center.x << " " << center.y << "\n";
		stream << " - size \t= " << size.x << " " << size.y << "\n";
		stream << " - position \t= " << position.x << " " << position.y << "\n";
		stream << " - max \t\t= " << max.x << " " << max.y << "\n";
		stream << " - min \t\t= " << min.x << " " << min.y << "\n";

		return stream.str();

	}

	void Rect::Set(float _x, float _y, float _w, float _h) {

		x = _x;
		y = _y;

		position = {_x, _y};
		size = {_w, _h};


		height = _h;
		width = _w;

		center = {x + (width / 2), y + (height / 2)};

		xMax = x + width;
		xMin = x;

		yMax = y + height;
		yMin = y;

		max = {xMax, yMax};
		min = {xMin, yMin};

		topleft = min;
		topright = {xMax, yMin};
		bottomleft = {xMin, yMax};
		bottomright = max;
		left = {xMin, y + (height /2)};
		right = {xMax, y + (height /2)};
		top = {x + (width / 2), yMin};
		bottom = {x + (width / 2), yMax};
	}

	void Rect::SetX(float _x) {
		Set(_x, y, width, height);
	}

	void Rect::SetY(float _y) {
		Set(x, _y, width, height);
	}

	void Rect::SetWidth(float _w) {
		Set(x, y, _w, height);
	}

	void Rect::SetHeight(float _h) {
		Set(x, y, width, _h);
	}

	void Rect::SetXMax(float _x) {
        Set(x, y, (_x - x), height);
	}

	void Rect::SetYMax(float _y) {
        Set(x, (_y - y), x, height);
	}

	void Rect::SetXMin(float _x) {
        Set(_x, y, (xMax - _x), height);
	}

	void Rect::SetYMin(float _y) {
         Set(x, _y, width, (yMax - _y));
	}

	void Rect::SetPosition(vec2 _p) {
		Set(_p.x, _p.y, width, height);
	}

	void Rect::SetCenter(vec2 _p) {
		Set(_p.x - (width / 2), _p.y - (height / 2), width, height);
	}

	void Rect::SetSize(vec2 _p) {
		Set(x, y, _p.x, _p.y);
	}

	void Rect::SetMax(vec2 _max) {
		Set(x, y, (_max.x - x), (_max.y - y));
	}

	void Rect::SetMin(vec2 _min) {
		Set(_min.x, _min.y, (xMax - _min.x), (yMax - _min.y));
	}

	vector<vec2> Rect::GetVertices() {
		return {
			topleft, topright, bottomright, bottomleft
		};
	}

	vector<vec3> Rect::GetVertices3D() {
		return {
			{topleft.x, topleft.y, 0.0f},
			{topright.x, topright.y, 0.0f},
			{bottomright.x, bottomright.y, 0.0f},
			{bottomleft.x, bottomleft.y, 0.0f}
		};
	}

	Rect Rect::zero = {0.0f, 0.0f, 0.0f, 0.0f};
}
