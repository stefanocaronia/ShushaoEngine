#pragma once

#include "pch/std.h"

#include "scenemanager.h"

namespace se {

class Cycle {
public:
    enum class Stage {
        INIT,
        UPDATE,
        FIXED,
        RENDER,
        EXIT
    };

    Cycle();
    ~Cycle();

    std::string name;

    bool init();
    void run();
    void stop();

protected:
    // pure virtual (devo implementare x forza)
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
};
}  // namespace se

extern se::Cycle* GAME;
