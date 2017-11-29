#include "debug.h"
#include "utility.h"

#include <iostream>
#include <string>
#include <sstream>
#include <typeinfo>

using namespace std;

namespace ShushaoEngine {

	namespace util {

		string basename(string filename) {
			string n = filename.substr(filename.find_last_of("/\\") + 1);
			return n.substr(0, n.find_last_of("."));
		}

		string zerofill(int number, int lenght) {

			ostringstream out;
			string sNumber = toString(number);

			for (unsigned int i = 0; i < lenght - sNumber.size(); i++) {
				out << "0";
			}

			out << sNumber;

			return out.str();
		}

		string classtitle(string type) {
			regex pat("N13ShushaoEngine|P6|P");
			type = regex_replace(type, pat, "");

			pat = "E$";
			type = regex_replace(type, pat, "");

			string title;
			bool inName = false;
			for (char& c : type) {
				if (isdigit(c) && !inName) continue;
				if (isupper(c) && inName) title += " ";
				title += (inName?c:toupper(c));
				inName = true;
			}
			return title;
		}

	}


	// vector_map

	vector_map::vector_map() {
		for (string i : defaults) {
			if (size() >= maxElements) return;
			push_back(i);
		}
	}

	vector_map::vector_map(initializer_list<string> ilist) {
		for (string i : ilist) {
			if (size() >= maxElements) return;
			push_back(i);
		}
	}

	void vector_map::operator= (initializer_list<string> ilist) {
		clear();
		for (string i : defaults) {
			if (size() >= maxElements) return;
			push_back(i);
		}
		for (string i : ilist) {
			if (size() >= maxElements) return;
			push_back(i);
		}
	}

	void vector_map::operator+= (string label) {
		if (size() >= maxElements) return;
		push_back(label);
	}

	void vector_map::operator-= (string label) {
		erase(remove(begin(), end(), label), end());
	}

	int vector_map::operator[] (string label) {
		auto it = find(begin(), end(), label);
		if (it != end()) {
			auto d = std::distance(begin(), it);
			return d;
		}
		return -1;
	}

	string vector_map::operator[] (unsigned int index) {
		if (index == maxElements) return "^overall";
		if (index > (size() + 1)) return "?undefined";
		return at(index);
	}

	void vector_map::setDefaults(initializer_list<string> ilist) {
		for (string i : ilist) defaults.push_back(i);
		for (string i : ilist) push_back(i);
	}

	int vector_map::top() {
        return size() - 1;
	}

	int vector_map::over() {
        return maxElements;
	}

	void vector_map::setMaxElements(unsigned int m) {
		maxElements = m;
	}

	void vector_map::toString(string title) {
		Logger::setColor(ConsoleColor::GREY);
		cout << " " << util::classtitle(typeid(*this).name()) << " " << title << " [" << maxElements << "] :" << endl;
		for (auto it = begin(); it != end(); ++it) {
			int key = std::distance(begin(), it);
            cout << "  (" << key << ") " << *it << endl;
		}
		// cout << "  (" << maxElements << ") " << "^overall" << endl;
		Logger::setColor(ConsoleColor::LIGHTGREY);
	}

}
