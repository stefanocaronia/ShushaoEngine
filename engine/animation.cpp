#include <iostream>

#include "debug.h"
#include "animation.h"
#include "base/time.h"
#include "timeline.h"

namespace se {

	using namespace std;

	Animation::~Animation() {
		Stop();
		for (Timeline* layer : layers) {
            if (layer != nullptr) delete(layer);
		}
		layers.clear();
	}

	int Animation::getFPS() {
		return fps;
	}

	void Animation::setFPS(int _fps) {
		fps = _fps;
		initialize();
	}

	Timeline* Animation::addLayer(string _name) {
		Timeline* timeline = new Timeline(_name);
		layers.push_back(timeline);
		return timeline;
	}

	Timeline* Animation::getLayer(string _name) {
		if (layers.empty()) return nullptr;
		for(Timeline* layer : layers) {
			if (layer->name == _name) return layer;
		}
		return nullptr;
	}

	void Animation::loadFrame(unsigned int nFrame) {
		if (!ready || layers.empty()) return;
		for(Timeline* layer : layers) {
			layer->loadFrame(nFrame);
		}
	}

	void Animation::reset() {
		if (!ready || layers.empty()) return;
		for(Timeline* layer : layers) {
			layer->reset();
		}
	}

	int Animation::getFrameCount() {
		if (layers.empty()) return 0;
		int maxCount = 0;
		for (Timeline* layer : layers) {
			int c = layer->getFrameCount();
			if (c  > maxCount) maxCount = c;
		}
		return maxCount;
	}

	void Animation::Play() {
		if (!ready || layers.empty()) return;
		//Debug::Log(INFO, "PLAY");
		for (Timeline* layer : layers) {
			layer->backup();
		}
		state = Playable::State::PLAY;
		animationTime = 0.0f;
		startTime = Time::GetTime();
	}

	void Animation::Stop() {
		if (!ready || layers.empty()) return;
		//Debug::Log(INFO, "STOP");
		reset();
		state = Playable::State::STOP;
		animationTime = 0.0f;
		startTime = 0.0f;
		cursor = 0;
	}

	void Animation::Pause() {
		if (!ready || layers.empty()) return;
		state = Playable::State::PAUSE;
	}

	void Animation::Awake() {
		if (layers.empty()) return;
		initialize();
		ready = true;
		state = Playable::State::STOP;
		if (startState == Playable::State::PLAY) Play();
	}

	void Animation::initialize() {
		frames = getFrameCount();
        frameDuration = 1.0f / (float)fps;
        duration = frames * frameDuration;

		//cout << "frames: " << frames << endl;
		//cout << "frameDuration: " << frameDuration << endl;
		//cout << "duration: " << duration << endl;
		//cout << "state: " << (int)state << endl;
	}

	void Animation::Update() {

		if (!ready || layers.empty()) return;
		if (state != Playable::State::PLAY) return;

		animationTime = Time::GetTime() - startTime;

		if (Time::GetTime() - lastFrameTime >= frameDuration) {

			loadFrame(cursor);

			if (++cursor >= frames || animationTime >= duration) {
				cursor = 0;
				if (!loop) Stop();
			}

			lastFrameTime = Time::GetTime();
		}
	}
}
