#pragma once

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

            float GetDuration() {
                return duration;
            }

            PlayableState GetState() {
                return state;
            }

            bool GetLoop() {
                return loop;
            }

            void SetState(PlayableState _state) {
                state = _state;
            }

            void SetStartState(PlayableState _state) {
                startState = _state;
            }

            void SetLoop(bool _loop) {
                loop = _loop;
            }

            void SetDuration(float _duration) {
                duration = _duration;
            }

        protected:

            double elapsed = 0.0;

    };
}