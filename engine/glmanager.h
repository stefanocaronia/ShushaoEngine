#pragma once

#include <freetype_.h>
#include <math_.h>
#include <opengl_.h>
#include <sdl_.h>
#include <std_.h>

namespace se {

class GLManager {
public:
    static SDL_GLContext gContext;
    static SDL_Window* gWindow;
    static SDL_Renderer* gRenderer;
    static FT_Library lFreetype;

    static bool fullscreen;
    static bool ready;
    static unsigned int DESKTOP_WIDTH;
    static unsigned int DESKTOP_HEIGHT;
    static unsigned int WIDTH;
    static unsigned int HEIGHT;
    static float ASPECT;
    static glm::vec2 VIEWPORT;

    static bool Init(std::string, bool);
    static void Quit();
    static void Clear();
    static void Clear(float, float, float, float, float);
    static void SetFullscreen(bool);
    static void ToggleFullscreen();
    static void Swap();
    static void Reset();
    static void Update();
};

}  // namespace se
