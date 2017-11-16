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
		LOG(INFO, "Cancello le resources " + Utility::toString(Assets.size()));
		vector<Object*> toDelete;
		for (auto const& asset : Assets) {
			toDelete.push_back(Assets[asset.first]);
		}

		for (Object* obj : toDelete) {
			LOG(INFO, "Cancello " + obj->name + " (" + Utility::toString(obj) +")");
			delete(obj);
		}
		Assets.clear();
	}

	map<string, Object*> Resources::Assets;
}
