#include "utility.h"
#include "debug.h"
#include "resources.h"
#include "object.h"
#include "shader.h"
#include "texture.h"
#include <exception>
#include <iostream>

using namespace std;

namespace ShushaoEngine {

	void Resources::Clear() {
		LOG("Cancello le resources (" + ts(Assets.size()) + ")");
		vector<Object*> toDelete;
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
		cout << " Resources [" << Assets.size() << "] :" << endl;
		for (auto const& asset : Assets) {
            cout << "  - (" << util::classtitle(typeid(*asset.second).name()) << ") " << asset.first << endl;
		}
		Logger::setColor(ConsoleColor::LIGHTGREY);
	}

	map<string, Object*> Resources::Assets;
}
