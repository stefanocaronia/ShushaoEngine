#include <exception>
#include <iostream>
#include <vector>

#include "debug.h"
#include "object.h"
#include "resources.h"
#include "shader.h"
#include "texture.h"
#include "utility.h"

namespace se {

using namespace std;

void Resources::Clear() {
    for (auto& asset : Assets) {
        if (asset.second != nullptr) {
            Debug::Log << "Cancello " << asset.second->name << " (" + util::classtitle(typeid(*asset.second).name()) + ")" << endl;
            delete (asset.second);
            asset.second = nullptr;
        }
    }
    Assets.clear();
}

void Resources::toString() {
    Logger::setColor(ConsoleColor::DARKBLUE);
    cout << " Resources [" << Assets.size() << "] :" << endl;
    for (auto const& asset : Assets) {
        cout << "  - (" << util::classtitle(typeid(*asset.second).name()) << ") " << asset.first << endl;
    }
    Logger::setColor(ConsoleColor::LIGHTGREY);
}

map<string, Object*> Resources::Assets;

}  // namespace se
