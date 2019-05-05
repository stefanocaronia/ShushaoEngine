#pragma once

#include "Core.h"
#include "sepch.h"

#include "levelmap.h"
#include "utility.h"

#define USER_CONFIG_FILE "config/config.ini"

namespace Config {

extern SHUSHAO_API std::string title;
extern SHUSHAO_API std::string startScene;
extern SHUSHAO_API bool debug;

// textures
extern unsigned int SHUSHAO_API pixelPerUnit;

// display
extern SHUSHAO_API float displayAspect;
extern SHUSHAO_API unsigned int displayWidth;
extern SHUSHAO_API unsigned int displayHeight;
extern SHUSHAO_API bool fullscreen;
extern SHUSHAO_API const std::map<std::string, std::pair<int, int>> DisplayModes;

// time
namespace Time {
    extern SHUSHAO_API float fixedRateLimit;  // 0.0f -> unlimited
    extern SHUSHAO_API float frameRateLimit;  // 0.0f -> unlimited
}  // namespace Time

// Physics (box2d)
namespace Physics {
    extern SHUSHAO_API bool enabled;
    extern SHUSHAO_API bool debug;
    extern SHUSHAO_API glm::vec2 gravity;
    extern SHUSHAO_API bool doSleep;
    extern SHUSHAO_API int velocityIterations;
    extern SHUSHAO_API int positionIterations;
}  // namespace Physics

extern SHUSHAO_API se::LevelMap Layers;
extern SHUSHAO_API se::LevelMap SortingLayers;

extern std::map<std::string, std::string> data;
extern SHUSHAO_API bool LoadUserConfig();
extern SHUSHAO_API bool LoadEngineConfig();
extern SHUSHAO_API bool parseUserConfig();
extern SHUSHAO_API bool parseEngineConfig();

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
