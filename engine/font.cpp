#include <string>
#include <SDL_image.h>

#include "font.h"
#include "debug.h"
#include "utility.h"
#include "glmanager.h"
#include "resources.h"

namespace se {

	Font::Font(std::string filename, std::string n) {
		if (filename != "") Load(filename);
		name = (n == "" ? util::basename(filename) : n);
	}

	Font::~Font() {
        delete(face);
    }

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

	bool Font::LoadEmbedded(int IDRES, std::string library) {
		vector<char> data = Resources::GetEmbeddedData(IDRES, library, RT_FONT);
		//bytes = (FT_Byte*)(data.data());
        if (bytes != nullptr) delete(bytes);
        bytes = new FT_Byte[data.size()];
        std::copy(data.begin(), data.end(), bytes);
		FT_Error r = FT_New_Memory_Face(GLManager::lFreetype, bytes, data.size() * sizeof(char), 0, &face);
		return r == 0;
	}


}
