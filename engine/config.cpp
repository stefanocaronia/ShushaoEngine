
#include <fstream>

#include "config.h"
#include "debug.h"
#include "globals.h"
#include "levelmap.h"
#include "resources.h"
#include "time.h"
#include "utility.h"

namespace Config {

using namespace std;

string title = "Shushao Engine";
string startScene = "";
bool debug = false;

// textures
unsigned int pixelPerUnit = 16;

// display
float displayAspect = 16.0f / 9.0f;
int displayWidth = 1024;
int displayHeight = (int)(displayWidth / displayAspect);
bool fullscreen = false;
const std::map<std::string, std::pair<int, int>> DisplayModes{
    {"1920x1080", {1920, 1080}},
    {"1400x1600", {1400, 1600}},
    {"1280x1024", {1280, 1024}},
    {"1024x576", {1024, 576}},
    {"1024x768", {1024, 768}}};

// Time
namespace Time {
    float fixedRateLimit = 60.0f;  // 0.0f -> unlimited
    float frameRateLimit = 0.0f;  // 0.0f -> unlimited
}  // namespace Time

// Physics (Box2d)
namespace Physics {
    bool enabled = true;
    bool debug = false;
    glm::vec2 gravity = {0, -8.8};
    bool doSleep = true;
    int velocityIterations = 8;
    int positionIterations = 3;
}  // namespace Physics

se::LevelMap Layers;
se::LevelMap SortingLayers;

std::map<std::string, std::string> data;
/*
	caricamento configurazione user
*/
bool LoadUserConfig() {
    ifstream cfile;
    cfile.open(USER_CONFIG_FILE);

    if (!cfile.is_open()) {
        se::Debug::Log(se::ERROR) << "Can't load user config from " << USER_CONFIG_FILE << endl;
        return false;
    }

    if (!processConfigData<ifstream>(cfile)) {
        cfile.close();
        return false;
    }

    cfile.close();

    if (!parseUserConfig()) {
        se::Debug::Log(se::ERROR) << "Can't parse user config" << endl;
        return false;
    }

    return true;
}

/*
	caricamento configurazione engine
*/
bool LoadEngineConfig() {

    string engine_config = se::Resources::GetEmbeddedText(CONFIG_ENGINE, LIB_SHUSHAO);

    if (engine_config == "") {
        se::Debug::Log(se::ERROR) << "Can't load engine config" << endl;
        return false;
    }

    std::istringstream cstring(engine_config);

    if (!processConfigData<istringstream>(cstring)) {
        return false;
    }

    if (!parseUserConfig()) {
        se::Debug::Log(se::ERROR) << "Can't parse user config" << endl;
        return false;
    }

    if (!parseEngineConfig()) {
        se::Debug::Log(se::ERROR) << "Can't parse engine config" << endl;
        return false;
    }

    return true;
}

bool parseUserConfig() {
    if (data.find("mode") != data.end()) {
        auto mode = DisplayModes.find(data["mode"]);
        if (mode != DisplayModes.end()) {
            displayWidth = mode->second.first;
            displayHeight = mode->second.second;
            displayAspect = displayWidth / displayHeight;
        }
    }

    if (data.find("fullscreen") != data.end()) {
        fullscreen = (data["fullscreen"] == "Y");
    }

    return true;
}

bool parseEngineConfig() {
    if (data.find("title") != data.end()) {
        title = data["title"];
    }

    if (data.find("start_scene") != data.end()) {
        startScene = data["start_scene"];
    }

    if (data.find("framerate_limit") != data.end()) {
        Time::frameRateLimit = stof(data["framerate_limit"]);
        Time::fixedRateLimit = stof(data["framerate_limit"]);
    }

    if (data.find("fixedrate_limit") != data.end()) {
        Time::fixedRateLimit = stof(data["fixedrate_limit"]);
    }

    if (data.find("pixel_per_unit") != data.end()) {
        pixelPerUnit = stoi(data["pixel_per_unit"]);
    }

    if (data.find("debug_enabled") != data.end()) {
        se::Debug::enabled = (data["debug_enabled"] == "Y");
    }

    if (data.find("physics_debug") != data.end()) {
        Physics::debug = (data["physics_debug"] == "Y");
    }

    if (data.find("debug_level") != data.end()) {
        if (data["debug_level"] == "INFO")
            se::Debug::level = se::DebugLevel::INFO;
        else if (data["debug_level"] == "WARNING")
            se::Debug::level = se::DebugLevel::WARNING;
        else if (data["debug_level"] == "ERROR")
            se::Debug::level = se::DebugLevel::ERROR;
    }

    if (data.find("debuggrid_mode") != data.end()) {
        if (data["debuggrid_mode"] == "ORTHOGRAFIC")
            se::Debug::debugGridMode = se::GridMode::ORTHOGRAFIC;
        else if (data["debuggrid_mode"] == "PERSPECTIVE")
            se::Debug::debugGridMode = se::GridMode::PERSPECTIVE;
    }

    if (data.find("layers") != data.end()) {
        Config::Layers = se::util::split(data["layers"], ',');
    }

    if (data.find("sorting_layers") != data.end()) {
        Config::SortingLayers = se::util::split(data["sorting_layers"], ',');
    }

    if (data.find("max_layers") != data.end()) {
        Config::Layers.setMaxElements(stoi(data["max_layers"]));
    }

    if (data.find("max_sorting_layers") != data.end()) {
        Config::SortingLayers.setMaxElements(stoi(data["max_sorting_layers"]));
    }

    return true;
}

}  // namespace Config
