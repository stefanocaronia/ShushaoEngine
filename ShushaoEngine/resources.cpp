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
		LOG(INFO, "Cancello le resources (" + ts(Assets.size()) + ")");
		vector<Object*> toDelete;
		for (auto const& asset : Assets) {
			if (Assets[asset.first] == nullptr) continue;
			toDelete.push_back(Assets[asset.first]);
		}

		for (Object* obj : toDelete) {
			if (obj == nullptr) continue;
			LOG(INFO, "Cancello " + obj->name + " (" + util::toString(obj) +")");
			delete(obj);

		}
		Assets.clear();
	}

	void Resources::toString() {
		Debug::SetColor(ConsoleColor::DARKYELLOW);
		cout << " Resources [" << Assets.size() << "] :" << endl;
		for (auto const& asset : Assets) {
            cout << "  - (" << util::classtitle(typeid(*asset.second).name()) << ") " << asset.first << endl;
		}
		Debug::SetColor(ConsoleColor::LIGHTGREY);
	}

	map<string, Object*> Resources::Assets;
}
