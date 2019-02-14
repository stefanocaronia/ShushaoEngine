#include <string>
#include <SDL_image.h>

#include "font.h"
#include "debug.h"
#include "utility.h"
#include "glmanager.h"

namespace se {

	Font::Font(std::string filename, std::string n) {
		if (filename != "") Load(filename);
		name = (n == "" ? util::basename(filename) : n);
	}

	Font::~Font()	{}

	void Font::setSize(int size_) {
        _size = size_;
        FT_Set_Pixel_Sizes(face, 0, _size);
    }

	bool Font::Load(std::string filename) {
		if (FT_New_Face(GLManager::lFreetype, filename.c_str(), 0, &face)) {
            return false;
		}
		return true;
	}

}
