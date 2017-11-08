#include "asset.h"

using namespace std;

namespace ShushaoEngine {

	Asset::Asset() {}

	Asset::Asset(string filename, string n) {
		Load(filename);
		name = n;
	}

	Asset::Asset(string filename) {

		Load(filename);

		name = filename.substr(filename.find_last_of("/\\") + 1);
		name = name.substr(0, name.find_last_of("."));
		name = filename;
	}

	bool Asset::Load(string filename) {

		// implement in derived classes

		return true;
	}

	string Asset::basename(string filename) {
		string n = filename.substr(filename.find_last_of("/\\") + 1);
		return n.substr(0, name.find_last_of("."));
	}

}
