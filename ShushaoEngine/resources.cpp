#include <exception>
#include <iostream>
#include <vector>

#include "utility.h"
#include "debug.h"
#include "resources.h"
#include "object.h"
#include "shader.h"
#include "texture.h"

namespace ShushaoEngine {

	void Resources::Clear() {
		std::vector<Object*> toDelete;
		for (auto const& asset : Assets) {
			if (Assets[asset.first] == nullptr) continue;
			toDelete.push_back(Assets[asset.first]);
		}

		for (Object* obj : toDelete) {
			if (obj == nullptr) continue;
			LOG("Cancello " + obj->name + " (" + util::toString(obj) +")");
			delete(obj);

		}
		Assets.clear();
	}

	void Resources::toString() {
		Logger::setColor(ConsoleColor::DARKYELLOW);
		std::cout << " Resources [" << Assets.size() << "] :" << std::endl;
		for (auto const& asset : Assets) {
            std::cout << "  - (" << util::classtitle(typeid(*asset.second).name()) << ") " << asset.first << std::endl;
		}
		Logger::setColor(ConsoleColor::LIGHTGREY);
	}

	std::map<std::string, Object*> Resources::Assets;
}
