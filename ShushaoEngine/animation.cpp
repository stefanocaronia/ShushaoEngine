#include <iostream>

#include "debug.h"
#include "animation.h"
#include "setime.h"

namespace ShushaoEngine {

	using namespace std;

	Animation::~Animation() {
		stop();
		for (Timeline* layer : layers) {
            if (layer != nullptr) delete(layer);
		}
		layers.clear();
	}

	int Animation::getFPS() {
		return fps;
	}

	float Animation::getDuration() {
		return duration;
	}

	AnimationState Animation::getState() {
		return state;
	}

	bool Animation::getLoop() {
		return loop;
	}

	void Animation::setFPS(int _fps) {
		fps = _fps;
		setup();
	}

	void Animation::setState(AnimationState _state) {
		state = _state;
	}

	void Animation::setStartState(AnimationState _state) {
		startState = _state;
	}

	void Animation::setLoop(bool _loop) {
		loop = _loop;
	}

	void Animation::setDuration(float _duration) {
		duration = _duration;
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

	void Animation::play() {
		if (!ready || layers.empty()) return;
		//Debug::Log(INFO, "PLAY");
		for (Timeline* layer : layers) {
			layer->backup();
		}
		state = AnimationState::PLAY;
		animationTime = 0.0f;
		startTime = Time::GetTime();
	}

	void Animation::stop() {
		if (!ready || layers.empty()) return;
		//Debug::Log(INFO, "STOP");
		reset();
		state = AnimationState::STOP;
		animationTime = 0.0f;
		startTime = 0.0f;
		cursor = 0;
	}

	void Animation::pause() {
		if (!ready || layers.empty()) return;
		state = AnimationState::PAUSE;
	}

	void Animation::Awake() {
		if (layers.empty()) return;
		setup();
		ready = true;
		state = AnimationState::STOP;
		if (startState == AnimationState::PLAY) play();
	}

	void Animation::setup() {
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
		if (state != AnimationState::PLAY) return;

		animationTime = Time::GetTime() - startTime;

		if (Time::GetTime() - lastFrameTime >= frameDuration) {

			loadFrame(cursor);

			if (++cursor >= frames || animationTime >= duration) {
				cursor = 0;
				if (!loop) stop();
			}

			lastFrameTime = Time::GetTime();
		}
	}
}
