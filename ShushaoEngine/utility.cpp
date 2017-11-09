#include "utility.h"

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

namespace ShushaoEngine {

	string Utility::basename(string filename) {
		string n = filename.substr(filename.find_last_of("/\\") + 1);
		return n.substr(0, n.find_last_of("."));
	}

	string Utility::zerofill(int number, int lenght) {

		ostringstream out;
		string sNumber = toString(number);

		for (unsigned int i = 0; i < lenght - sNumber.size(); i++) {
			out << "0";
		}

		out << sNumber;

		return out.str();
	}


}
