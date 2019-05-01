#include "glmanager.h"
#include "Application.h"
#include "config.h"
#include "inputinterface.h"

namespace se {

#define BIND_EVENT_FN(x) std::bind(&Application::x, self, std::placeholders::_1)

bool GLManager::Init(std::string title, bool fs) {
    window = std::unique_ptr<Window>(Window::Create());
    // window->SetEventCallback(BIND_EVENT_FN(OnEvent));  // TODO: stavolta è static, questa cosa non funziona

    fullscreen = fs;

    WIDTH = Config::displayWidth;
    HEIGHT = Config::displayHeight;

    SDL_Init(SDL_INIT_EVERYTHING);  //  | SDL_INIT_JOYSTICK
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

    FT_Init_FreeType(&lFreetype);

    Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    Mix_AllocateChannels(16);

    SDL_GL_SetSwapInterval(1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    /* SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4); */
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_DisplayMode dm;
    SDL_GetDesktopDisplayMode(0, &dm);
    DESKTOP_WIDTH = dm.w;
    DESKTOP_HEIGHT = dm.h;

    if (fullscreen) {
        gWindow = SDL_CreateWindow(title.c_str(), 0, 0, DESKTOP_WIDTH, DESKTOP_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP);
    } else {
        gWindow = SDL_CreateWindow(title.c_str(), DESKTOP_WIDTH / 2 - WIDTH / 2, DESKTOP_HEIGHT / 2 - HEIGHT / 2, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
    }

    SDL_SetWindowResizable(gWindow, SDL_TRUE);

    //gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

    gContext = SDL_GL_CreateContext(gWindow);
    SDL_GL_MakeCurrent(gWindow, gContext);

    // Init GLEW
    // glewExperimental = GL_TRUE;
    // glewInit();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //glShadeModel(GL_SMOOTH);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_LEQUAL); // senza questo il 3d non funziona
    glDepthFunc(GL_ALWAYS);  // questo per il 2d
    /* glEnable(GL_MULTISAMPLE);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
		glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_POLYGON_SMOOTH); */

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Update();

    ready = true;
    return true;
}

void GLManager::Update() {
    window->OnUpdate();
    VIEWPORT = {(float)Config::displayWidth / (Config::pixelPerUnit / 2), (float)Config::displayHeight / (Config::pixelPerUnit / 2)};
    ASPECT = (float)WIDTH / (float)HEIGHT;
}

void GLManager::Quit() {
    // SDL_DestroyWindow(gWindow);
    // gWindow = NULL;
    // SDL_GL_DeleteContext(gContext);
    Mix_CloseAudio();
    Mix_Quit();
    SDL_Quit();
}

void GLManager::Clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearDepth(1.0f);
}

void GLManager::Clear(float r, float g, float b, float a, float depth = 1.0f) {
    glClearColor(r, g, b, a);
    glClearDepth(depth);
}

void GLManager::SetFullscreen(bool fs) {
    fullscreen = fs;
    if (fullscreen) {
        SDL_SetWindowFullscreen(gWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
        glViewport(0, 0, DESKTOP_WIDTH, DESKTOP_HEIGHT);
    } else {
        SDL_SetWindowFullscreen(gWindow, SDL_FALSE);
        SDL_GetWindowSize(gWindow, (int*)&WIDTH, (int*)&HEIGHT);
        glViewport(0, 0, WIDTH, HEIGHT);
    }
}

void GLManager::ToggleFullscreen() {
    SetFullscreen(!fullscreen);
}

void GLManager::Swap() {
    SDL_GL_SwapWindow(gWindow);
}

void GLManager::Reset() {
    Clear();
    // glLoadIdentity(); // old pipeline
}

// inizialize static properties

SDL_GLContext GLManager::gContext;
SDL_Window* GLManager::gWindow;
FT_Library GLManager::lFreetype = nullptr;

bool GLManager::fullscreen = false;
bool GLManager::ready = false;
//std::vector<Shader*> GLManager::shaders;

unsigned int GLManager::DESKTOP_WIDTH;
unsigned int GLManager::DESKTOP_HEIGHT;
unsigned int GLManager::WIDTH;
unsigned int GLManager::HEIGHT;
glm::vec2 GLManager::VIEWPORT;
float GLManager::ASPECT;

}  // namespace se
