#pragma once

#include <GL/glew.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "object.h"
#include "resource.h"

namespace se {

	class Font : public Object, public Resource {

		public:

			Font(std::string filename = "", std::string n = "");
			~Font();

			FT_Face face;

			const int& size = _size;

			bool Load(std::string);
			bool LoadEmbedded(int IDRES, std::string library = "");
			void SetSize(float);
			void SetPixelSize(int);

		private:

			int _size = 12;
	};

}
