#pragma once

#include "core.h"

#include "levelmap.h"
#include "utility.h"

#define USER_CONFIG_FILE "config/config.ini"

namespace Config {

extern std::string SHUSHAO_API title;
extern std::string SHUSHAO_API startScene;
extern bool SHUSHAO_API debug;

// textures
extern unsigned int SHUSHAO_API pixelPerUnit;

// display
extern float SHUSHAO_API displayAspect;
extern int SHUSHAO_API displayWidth;
extern int SHUSHAO_API displayHeight;
extern bool SHUSHAO_API fullscreen;
extern const std::map<std::string, std::pair<int, int>> SHUSHAO_API DisplayModes;

// time
namespace Time {
    extern float SHUSHAO_API fixedRateLimit;  // 0.0f -> unlimited
    extern float SHUSHAO_API frameRateLimit;  // 0.0f -> unlimited
}  // namespace Time

// Physics (box2d)
namespace Physics {
    extern bool SHUSHAO_API enabled;
    extern bool SHUSHAO_API debug;
    extern glm::vec2 SHUSHAO_API gravity;
    extern bool SHUSHAO_API doSleep;
    extern int SHUSHAO_API velocityIterations;
    extern int SHUSHAO_API positionIterations;
}  // namespace Physics

extern se::LevelMap SHUSHAO_API Layers;
extern se::LevelMap SHUSHAO_API SortingLayers;

extern std::map<std::string, std::string> data;
extern bool SHUSHAO_API LoadUserConfig();
extern bool SHUSHAO_API LoadEngineConfig();
extern bool SHUSHAO_API parseUserConfig();
extern bool SHUSHAO_API parseEngineConfig();

template <class T>
bool processConfigData(T& cstring) {
    std::vector<std::string> parts;
    std::string line, f;
    while (getline(cstring, line)) {
        if (line.size() == 0) continue;
        f = line.substr(0, 1);
        if (f == "#" || f == "/" || f == "[" || f == "*" || f == "[") continue;
        std::vector<std::string> parts = se::util::split(line, '=');
        if (parts.size() > 1) {
            //data.insert({parts[0], parts[1]});
            data[parts[0]] = parts[1];
        }
    }
    return true;
}
}  // namespace Config
