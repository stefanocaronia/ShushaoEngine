#pragma once

#include <GLFW/glfw3.h>

#include "Shushao/Core.h"
#include "Window.h"
#include "sepch.h"

namespace se {

class SHUSHAO_API GLManager {
public:
    static FT_Library lFreetype;

    static bool fullscreen;
    static bool ready;
    static unsigned int DESKTOP_WIDTH;
    static unsigned int DESKTOP_HEIGHT;
    static unsigned int WIDTH;
    static unsigned int HEIGHT;
    static float ASPECT;
    static glm::vec2 VIEWPORT;

    static bool Init();
    static void Quit();
    static void Update();
};

}  // namespace se
