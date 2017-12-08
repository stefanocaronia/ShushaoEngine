#pragma once

#include "gllibs.h"
#include "object.h"

namespace ShushaoEngine {

	class Music : public Object {

		public:

			Music(string filename = "");
			~Music();

			Mix_Music* track;

			bool Load(string);

			void play(int loops = 1);
			void fadeIn(int loops = 1, int ms = 1000);

			// STATIC

			static void resume();
			static void pause();
			static void stop();
			static void rewind();
			static void fadeOut(int ms = 1000);
			static void seek(double position);

			static int setVolume(int);
			static int addVolume(int);
			static int volumeDown(int);
			static int getVolume();
			static void mute();
			static void unMute();

			static bool isPlaying();
			static bool isPaused();
			static bool isFading();
			static bool isMuted();

		private:

			static bool muted;
			static int volume;

	};

}
