#pragma once

#include <vector>

#include "component.h"

namespace se {

	class Timeline;

	enum class AnimationState {
		STOP,
		PLAY,
		PAUSE
	};

	class Animation : public Component {

		public:

			~Animation();

			Timeline* addLayer(string);
			Timeline* getLayer(string);

			void setFPS(int);
			void setDuration(float);
			void setState(AnimationState);
			void setStartState(AnimationState);
			void setLoop(bool);

			int getFPS();
			float getDuration();
			int getFrameCount();
			AnimationState getState();
			bool getLoop();

			void play();
			void stop();
			void pause();

		protected:

			vector<Timeline*> layers;

			void setup();

			// lifecycle
			void Awake();
			void Update();

		private:

			AnimationState state = AnimationState::STOP;
			AnimationState startState = AnimationState::STOP;

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

}
