#include "resources.h"
#include "object.h"
#include "shader.h"
#include "texture.h"

using namespace std;

namespace ShushaoEngine {

	void Resources::Clean() {
		for (auto const& asset : Assets) {
			delete(Assets[asset.first]);
		}
		Assets.clear();
	}

	map<string, Object*> Resources::Assets;
}
