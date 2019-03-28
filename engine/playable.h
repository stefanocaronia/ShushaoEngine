#pragma once

namespace se {

class Playable {
public:

    enum class State {
        STOP,
        PLAY,
        PAUSE
    };

    virtual void Play() = 0;
    virtual void Stop() = 0;
    virtual void Pause() = 0;

    float GetDuration() {
        return duration;
    }

    Playable::State GetState() {
        return state;
    }

    bool GetLoop() {
        return loop;
    }

    void SetState(State value) {
        state = value;
    }

    void SetStartState(State value) {
        startState = value;
    }

    void SetLoop(bool value) {
        loop = value;
    }

    void SetDuration(float value) {
        duration = value;
    }

protected:
    double elapsed = 0.0;

    State state = State::STOP;
    State startState = State::STOP;

    float duration;
    bool loop;
};
}  // namespace se