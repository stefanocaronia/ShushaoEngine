#include "utility.h"

#include <string>


namespace ShushaoEngine {

	string Utility::basename(string filename) {
		string n = filename.substr(filename.find_last_of("/\\") + 1);
		return n.substr(0, n.find_last_of("."));
	}

}
