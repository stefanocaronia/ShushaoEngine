#pragma once

#include <glm.hpp>
#include <string>

using namespace glm;
using namespace std;

namespace ShushaoEngine {

	class Rect {

		public:

			Rect();
			Rect(float, float, float, float);

			static Rect zero;

			static Rect MinMaxRect(float, float, float, float);	// Creates a rectangle from min/max coordinate values.
			static vec2 NormalizedToPoint(Rect, vec2);	// Returns a point inside a rectangle, given normalized coordinates.
			static vec2 PointToNormalized(Rect, vec2);	// Returns the normalized coordinates cooresponding the the point.

			vec2 center;	// The position of the center of the rectangle.
			float height;	// The height of the rectangle, measured from the Y position.
			vec2 max;	// The position of the maximum corner of the rectangle.
			vec2 min;	// The position of the minimum corner of the rectangle.
			vec2 position;	// The X and Y position of the rectangle.
			vec2 size;	// The width and height of the rectangle.
			float width;	// The width of the rectangle, measured from the X position.
			float x;	// The X coordinate of the rectangle.
			float xMax;	// The maximum X coordinate of the rectangle.
			float xMin;	// The minimum X coordinate of the rectangle.
			float y;	// The Y coordinate of the rectangle.
			float yMax;	// The maximum Y coordinate of the rectangle.
			float yMin;	// The minimum Y coordinate of the rectangle.

			bool Contains(vec2);	// Returns true if the x and y components of point is a point inside this rectangle. If allowInverse is present and true, the width and height of the Rect are allowed to take negative values (ie, the min value is greater than the max), and the test will still work.
			bool Contains(vec3);

			bool Overlaps(Rect);	// Returns true if the other rectangle overlaps this one. If allowInverse is present and true, the widths and heights of the Rects are allowed to take negative values (ie, the min value is greater than the max), and the test will still work.
			void Set(float, float, float, float); 	 // Set components of an existing Rect.

			string ToString();	// TODO: Returns a nicely formatted string for this Rect.


			// operator == // TODO

			void SetX(float);
			void SetY(float);
			void SetWidth(float);
			void SetHeight(float);
			void SetXMax(float);
			void SetYMax(float);
			void SetXMin(float);
			void SetYMin(float);
			void SetPosition(vec2);
			void SetCenter(vec2);
			void SetSize(vec2);
			void SetMax(vec2);
			void SetMin(vec2);

		protected:

		private:

	};

}
