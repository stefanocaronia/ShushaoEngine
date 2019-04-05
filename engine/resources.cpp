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

vector<char> Resources::GetEmbeddedData(int IDRES, string library, LPCSTR type) {
    std::vector<char> output;

    HMODULE module;

    if (library != "") {
        module = LoadLibrary(library.c_str());
    } else {
        module = GetModuleHandle(NULL);
    }

    auto resourceHandle = FindResource(module, MAKEINTRESOURCE(IDRES), type);

    if (resourceHandle != nullptr) {
        auto dataHandle = LoadResource(module, resourceHandle);
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
    } else {
        Debug::Log(WARNING) << "Cant load Resource " << IDRES << (library != "" ? " from " + library : "") <<  endl;
        return vector<char>();
    }

    return output;
}

string Resources::GetEmbeddedText(int IDRES, std::string library) {
    auto data = se::Resources::GetEmbeddedData(IDRES, library, RT_RCDATA);
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
