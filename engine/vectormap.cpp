#include "debug.h"
#include "utility.h"

#include <iostream>
#include <string>
#include <sstream>
#include <typeinfo>

namespace ShushaoEngine {

	VectorMap::VectorMap() {
		for (string i : defaults) {
			if (size() >= maxElements) return;
			push_back(i);
		}
	}

	VectorMap::VectorMap(initializer_list<string> ilist) {
		for (string i : ilist) {
			if (size() >= maxElements) return;
			push_back(i);
		}
	}

	void VectorMap::operator= (initializer_list<string> ilist) {
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

	void VectorMap::operator+= (string label) {
		if (size() >= maxElements) return;
		push_back(label);
	}

	void VectorMap::operator-= (string label) {
		erase(remove(begin(), end(), label), end());
	}

	int VectorMap::operator[] (string label) {
		auto it = find(begin(), end(), label);
		if (it != end()) {
			auto d = std::distance(begin(), it);
			return d;
		}
		return -1;
	}

	string VectorMap::operator[] (unsigned int index) {
		if (index == maxElements) return "^overall";
		if (index > (size() + 1)) return "?undefined";
		return at(index);
	}

	void VectorMap::setDefaults(initializer_list<string> ilist) {
		for (string i : ilist) defaults.push_back(i);
		for (string i : ilist) push_back(i);
	}

	int VectorMap::top() {
        return size() - 1;
	}

	int VectorMap::over() {
        return maxElements;
	}

	void VectorMap::setMaxElements(unsigned int m) {
		maxElements = m;
	}

	void VectorMap::toString(string title) {
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
