#pragma once

#include <std_.h>

#include "component.h"
#include "playable.h"

namespace se {

class Timeline;

class Animation : public Component, public Playable {
public:
    virtual void setup() { name = "Animation"; }
    ~Animation();

    Timeline* addLayer(string);
    Timeline* getLayer(string);

    void setFPS(int);

    int getFPS();
    int getFrameCount();

    void Play();
    void Stop();
    void Pause();

    void Copy(Animation* other);

protected:
    vector<Timeline*> layers;

    void initialize();

    // lifecycle
    void Awake();
    void Update();

private:
    Playable::State state = Playable::State::STOP;
    Playable::State startState = Playable::State::STOP;

    bool loop = true;
    bool ready = false;

    float frames = 0;
    float duration = 0.0f;
    int fps = 20;
    float frameDuration = 1.0f / fps;
    unsigned int cursor = 0;
    float lastFrameTime = 0.0f;
    float animationTime = 0.0f;
    float startTime = 0.0f;

    void loadFrame(unsigned int);
    void reset();
};

}  // namespace se
