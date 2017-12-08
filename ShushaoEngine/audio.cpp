#include "audio.h"

#include "debug.h"
#include "utility.h"

namespace ShushaoEngine {

	Music::Music(std::string filename) {
		if (filename != "") Load(filename);
		name = util::basename(filename);
	}

	Music::~Music()	{
		if (track != nullptr) {
			Mix_FreeMusic(track);
			track = nullptr;
			//delete(track);
		}
	}

	bool Music::Load(std::string filename) {

		track = Mix_LoadMUS(filename.c_str());

		if (track == nullptr) {
			Debug::Log(ERROR) << "Impossibile caricare " << filename << ": " << Mix_GetError() << endl;
			return false;
		}

		return true;
	}

	void Music::play(int loops) {
		if (track == nullptr) return;
		if (Mix_PausedMusic() == 1) Mix_ResumeMusic();
		Mix_PlayMusic(track, loops);
		if (!muted) {
			volume = Mix_VolumeMusic(-1);
			muted = false;
		}
	}

	void Music::resume() {
		Mix_ResumeMusic();
	}

	void Music::pause() {
		Mix_PauseMusic();
	}

	void Music::stop() {
		Mix_HaltMusic();
	}

	void Music::rewind() {
		Mix_RewindMusic();
	}

	void Music::fadeIn(int loops, int ms) {
		if (track == nullptr) return;
		if (Mix_PausedMusic() == 1) Mix_ResumeMusic();
		Mix_FadeInMusic(track, loops, ms);
		muted = false;
	}

	void Music::fadeOut(int ms) {
		Mix_FadeOutMusic(ms);
	}

	bool Music::isPlaying() {
		return Mix_PlayingMusic() == 1 && Mix_PausedMusic() != 1;
	}

	bool Music::isPaused() {
		return Mix_PausedMusic() == 1 && Mix_PlayingMusic() == 1;
	}

	bool Music::isFading() {
		return Mix_FadingMusic() == 1;
	}

	bool Music::isMuted() {
		return muted;
	}

	void Music::seek(double position) {
		rewind();
		Mix_SetMusicPosition(position);
	}

	int Music::setVolume(int volume_) { // 0 - 128
		Mix_VolumeMusic(volume_);
		return volume = Mix_VolumeMusic(-1);
	}

	int Music::addVolume(int volume_) {
		setVolume(Mix_VolumeMusic(-1) + volume_);
		return volume = Mix_VolumeMusic(-1);
	}

	int Music::getVolume() {
		return Mix_VolumeMusic(-1);
	}

	void Music::mute() {
		Mix_VolumeMusic(0);
		muted = true;
	}

	void Music::unMute() {
		Mix_VolumeMusic(volume);
		muted = false;
	}

	bool Music::muted;
	int Music::volume;

}
