#include "levelmap.h"
#include "globals.h"
#include "debug.h"

namespace se {

using namespace std;

LevelMap::LevelMap() {
    for (string i : defaults) {
        if (size() >= maxElements) return;
        push_back(i);
    }
}

LevelMap::LevelMap(initializer_list<string> ilist) {
    for (string i : ilist) {
        if (size() >= maxElements) return;
        push_back(i);
    }
}

LevelMap::LevelMap(vector<std::string> list) {
    for (string i : list) {
        if (size() >= maxElements) return;
        push_back(i);
    }
}

void LevelMap::operator=(initializer_list<string> ilist) {
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

void LevelMap::operator+=(string label) {
    if (size() >= maxElements) return;
    push_back(label);
}

void LevelMap::operator-=(string label) {
    erase(remove(begin(), end(), label), end());
}

int LevelMap::operator[](string label) {
    auto it = find(begin(), end(), label);
    if (it != end()) {
        auto d = distance(begin(), it);
        return d;
    }
    return -1;
}

string LevelMap::operator[](unsigned int index) {
    if (index == maxElements) return "^overall";
    if (index > (size() + 1)) return "?undefined";
    return at(index);
}

void LevelMap::setDefaults(initializer_list<string> ilist) {
    for (string i : ilist) defaults.push_back(i);
    for (string i : ilist) push_back(i);
}

int LevelMap::top() {
    return size() - 1;
}

int LevelMap::over() {
    return maxElements;
}

void LevelMap::setMaxElements(unsigned int m) {
    maxElements = m;
}

void LevelMap::toString(string title) {
    Logger::setColor(ConsoleColor::GREY);
    cout << " " << util::classtitle(typeid(*this).name()) << " " << title << " [" << maxElements << "] :" << endl;
    for (auto it = begin(); it != end(); ++it) {
        int key = distance(begin(), it);
        cout << "  (" << key << ") " << *it << endl;
    }
    // cout << "  (" << maxElements << ") " << "^overall" << endl;
    Logger::setColor(ConsoleColor::LIGHTGREY);
}

}  // namespace se
