#pragma once

#include <GL/glew.h>

#include <ft2build.h>
#include FT_FREETYPE_H
#include "object.h"

namespace se {

	class Font : public Object {

		public:

			Font(std::string filename = "", std::string n = "");
			~Font();

			FT_Face face;

			const int& size = _size;

			bool Load(std::string);
			void setSize(int);

		private:

			int _size = 12;
	};

}
