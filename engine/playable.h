#pragma once;

namespace se {

    enum class PlayableState {
		STOP,
		PLAY,
		PAUSE
    };

    class Playable {
        public:

            PlayableState state = PlayableState::STOP;
			PlayableState startState = PlayableState::STOP;
            float duration;
            bool loop;

            virtual void Play() = 0;
            virtual void Stop() = 0;
            virtual void Pause() = 0;

            float getDuration() {
                return duration;
            }

            PlayableState getState() {
                return state;
            }

            bool getLoop() {
                return loop;
            }

            void setState(PlayableState _state) {
                state = _state;
            }

            void setStartState(PlayableState _state) {
                startState = _state;
            }

            void setLoop(bool _loop) {
                loop = _loop;
            }

            void setDuration(float _duration) {
                duration = _duration;
            }


    };
}