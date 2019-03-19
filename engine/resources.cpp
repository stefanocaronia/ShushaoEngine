#include <exception>
#include <iostream>
#include <vector>

#include "debug.h"
#include "object.h"
#include "resources.h"
#include "shaders/shader.h"
#include "texture.h"
#include "utility.h"

namespace se {

using namespace std;

vector<char> Resources::GetEmbeddedData(int IDRES, LPCSTR type) {
    std::vector<char> output;

    // If you need to retrieve resources embedded in a binary that is not the current running program, modify this
    // function to pass in a HMODULE value.
    HMODULE module = nullptr;

    auto resourceHandle = ::FindResource(module, MAKEINTRESOURCE(IDRES), type);

    if (resourceHandle != nullptr) {
        auto dataHandle = ::LoadResource(module, resourceHandle);
        if (dataHandle != nullptr) {
            auto resourceSize = ::SizeofResource(module, resourceHandle);
            if (resourceSize != 0) {
                auto firstByte = reinterpret_cast<const char*>(::LockResource(dataHandle));
                if (firstByte != nullptr) {
                    output.resize(resourceSize);
                    copy(firstByte, firstByte + resourceSize, output.begin());
                }
            }
        }
    }

    return output;
}

string Resources::GetEmbeddedText(int IDRES) {
    auto data = se::Resources::GetEmbeddedData(IDRES);
	return std::string(data.begin(), data.end());
}

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
