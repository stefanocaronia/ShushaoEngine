#pragma once

#include <string>
#include <glm/glm.hpp>

using namespace std;

namespace se {

	class Color {

		public:

			Color();
			Color(float, float, float, float a = 1.0f);

			float r; //	Red component of the color.
			float g; //	Green component of the color.
			float b; //	Blue component of the color.
			float a; //	Alpha component of the color.

			// Color* gamma; //	A version of the color that has had the gamma curve applied.
			// float grayscale; //	The grayscale value of the color. (Read Only)
			// Color linear; //	A linear value of an sRGB color.

			float maxColorComponent(); //	Returns the maximum color component value: Max(r,g,b).
			std::string ToString();

			glm::vec4 rgba;

			static Color black; // Solid black. RGBA is (0, 0, 0, 1).
			static Color blue; // Solid blue. RGBA is (0, 0, 1, 1).
			static Color clear; // Completely transparent. RGBA is (0, 0, 0, 0).
			static Color cyan; // Cyan. RGBA is (0, 1, 1, 1).
			static Color gray; // Gray. RGBA is (0.5, 0.5, 0.5, 1).
			static Color green; // Solid green. RGBA is (0, 1, 0, 1).
			static Color grey; // English spelling for gray. RGBA is the same (0.5, 0.5, 0.5, 1).
			static Color magenta; // Magenta. RGBA is (1, 0, 1, 1).
			static Color red; // Solid red. RGBA is (1, 0, 0, 1).
			static Color white; // Solid white. RGBA is (1, 1, 1, 1).
			static Color yellow; // Yellow. RGBA is (1, 0.92, 0.016, 1), but the color is nice to look at!

			bool operator==(Color& other) {
				return (r == other.r &&
						g == other.g &&
						b == other.b &&
						a == other.a);
			}

	};

}
