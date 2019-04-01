
#include <fstream>

#include "config.h"
#include "levelmap.h"
#include "utility.h"
#include "globals.h"
#include "debug.h"
#include "resources.h"

namespace Config {

	using namespace std;

	string title = "Shushao Engine";
	bool debug = false;

	// textures
	unsigned int pixelPerUnit = 16;

	// display
	float displayAspect	= 16.0f / 9.0f;
	int displayWidth = 1024;
	int displayHeight = (int)(displayWidth / displayAspect);
	bool fullscreen = false;
	const std::map<std::string, std::pair<int, int>> DisplayModes{
		{"1920x1080", {1920, 1080}},
		{"1400x1600", {400, 1600}},
		{"1280x1024", {1280, 1024}},
		{"1024x576", {1024, 576}},
		{"1024x768", {1024, 768}}};

	// Time
	namespace Time {
		float fixedRateLimit = 60.0f; // 0.0f -> unlimited
		float frameRateLimit = 0.0f; // 0.0f -> unlimited
	}

	// Physics (Box2d)
	namespace Physics {

		bool enabled = true;
		bool debug = false;
		glm::vec2 gravity = {0, -8.8};
		bool doSleep = true;
		int velocityIterations = 8;
		int positionIterations = 3;

	}

	se::LevelMap Layers;
	se::LevelMap SortingLayers;

	std::map<std::string, std::string> data;

	void LoadUserConfig() {
		ifstream cfile;
		cfile.open(USER_CONFIG_FILE);

		if (!cfile.is_open()) {
			se::Debug::Log(se::ERROR) << "Can't load user config from " << USER_CONFIG_FILE << endl;
		}

		string key,line,f;

		while(getline(cfile, line)) {
			if (line.size()==0) continue;
			f=line.substr(0,1);
			if (f=="#"||f=="/"||f=="["||f=="*"||f=="[") continue;
			vector<string> parts = se::util::split(line,'=');
			if (parts.size()>1) data.insert({parts[0], parts[1]});
		}

		cfile.close();

		if (data.find("mode") != data.end()) {
			auto mode = DisplayModes.find(data["mode"]);
			if (mode != DisplayModes.end()) {
				displayWidth = mode->second.first;
				displayHeight = mode->second.second;
				displayAspect = displayWidth / displayHeight;
			}
		}

		if (data.find("fullscreen") != data.end()) {
			fullscreen = data["fullscreen"] == "Y";
		}
	}

	void LoadEngineConfig() {

		string engine_config = se::Resources::GetEmbeddedText(CONFIG_ENGINE);

		std::istringstream cstring(engine_config);

		string key,line,f;

		while(getline(cstring, line)) {

			if (line.size()==0) continue;
			f=line.substr(0,1);
			if (f=="#"||f=="/"||f=="["||f=="*"||f=="[") continue;
			vector<string> parts = se::util::split(line,'=');
			if (parts.size()>1) data.insert({parts[0], parts[1]});
		}

		if (data.find("title") != data.end()) {
			title = data["title"];
		}

	}

}
