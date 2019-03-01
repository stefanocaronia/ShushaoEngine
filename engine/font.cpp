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

	void Font::SetSize(float wsize_) {
        SetPixelSize(wsize_ * Config::pixelPerUnit);
    }

    void Font::SetPixelSize(int size_) {
    	 _size = size_;
        FT_Set_Pixel_Sizes(face, 0, _size);
    }

	bool Font::Load(std::string filename) {
		if (FT_New_Face(GLManager::lFreetype, filename.c_str(), 0, &face)) {
			Debug::Log(ERROR) << "Could not load font: " << filename << endl;
            return false;
		}
		return true;
	}

}
