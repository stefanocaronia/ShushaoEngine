#pragma once

#include "Core.h"
#include "Window.h"
#include "events/ApplicationEvent.h"
#include "scenemanager.h"

namespace se {

class SHUSHAO_API Application {
public:
    enum class Stage {
        INIT,
        UPDATE,
        FIXED,
        RENDER,
        EXIT
    };

    Application();
    virtual ~Application();

    std::string name;

    bool Init();
    void Run();
    void Stop();

    inline static Application& Get() { return *instance; }

    void OnEvent(Event& e);

protected:
    virtual void Awake(){};
    virtual void Start(){};
    virtual void GetInput(){};
    virtual void Update(){};
    virtual void FixedUpdate(){};
    virtual void Render(){};
    virtual void End(){};

    virtual bool InitResources() = 0;  // resources loading
    virtual bool InitConfig() = 0;  // config override
    virtual bool InitMapping() = 0;  // input mapping
    virtual bool InitScene() = 0;  // scene load

    bool RUNNING = true;
    bool READY = false;

    bool keys[350];

private:
    void initscan();
    void update();
    void render();
    void fixed();
    void exit();

    bool OnWindowClose(WindowCloseEvent& e);

    static Application* instance;
};

// To be defined in CLIENT
Application* CreateApplication();

}  // namespace se
