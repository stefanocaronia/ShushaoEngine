#include <SDL_image.h>
#include <string>
#include <fstream>

#include "debug.h"
#include "resources.h"
#include "textfile.h"
#include "utility.h"

namespace se {

using namespace std;

Textfile::Textfile(std::string filename, std::string n) {
    if (filename != "") Load(filename);
    name = (n == "" ? util::basename(filename) : n);
}

Textfile::~Textfile() {}

bool Textfile::LoadEmbedded(int IDRES, std::string library) {
    auto data = Resources::GetEmbeddedText(IDRES, library);
    text = std::string(data.begin(), data.end());
	return true;
}

bool Textfile::Load(std::string filename) {
    name = util::basename(filename);
	buffer.clear();
	ifstream t(filename);
	buffer << t.rdbuf();
	text = buffer.str();

	return true;
}

}  // namespace se
