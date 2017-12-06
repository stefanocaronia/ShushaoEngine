#include <string>
#include <iostream>

#include "inputmanager.h"
#include "gllibs.h"
#include "cycle.h"
#include "setime.h"
#include "glmanager.h"
#include "system.h"
#include "debug.h"

using namespace std;

namespace ShushaoEngine {

	InputManager::InputManager() {
		name = "Input Manager";
	}

	InputManager::~InputManager() {
		for (auto const& m : inputs) {
			delete(m.second);
		}
		inputs.clear();
	}

	InputMapping* InputManager::addMapping(string name_) {
		InputMapping* input = new InputMapping();
		input->name = name_;
		inputs[name_] = input;
		return input;
	}

	InputMapping* InputManager::getMapping(string name_) {
		return inputs[name_];
	}

	void InputManager::addController(int index) {
		if (SDL_IsGameController(index)) {
			SDL_GameController* gc = SDL_GameControllerOpen(index);
			SDL_JoystickID id = SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(gc));
			ControllerDevice cd = {
				index,
				id,
				nullptr,
				gc
			};
			controllers.insert({id, cd});
		} else {
			SDL_Joystick* j = SDL_JoystickOpen(index);
			SDL_JoystickID id = SDL_JoystickInstanceID(j);
			controllers.insert({id, {
				index,
				id,
				j,
				nullptr
			}});
		}
	}

	void InputManager::removeController(int instance) {
		SDL_GameController* gc = controllers.at(instance).controller;
		SDL_GameControllerClose(gc);
		controllers.erase(instance);
	}

	void InputManager::printActiveControllers() {
		Logger::setColor(ConsoleColor::RED);
		cout << " InputManager Active Controllers:" << endl;
		for (auto cm : controllers) {
			ControllerDevice cd = cm.second;
			if (cd.controller != nullptr) cout << "  - (" << cd.index << ") [" << cd.instanceID << "] " << SDL_GameControllerName(cd.controller) << endl;
			if (cd.joystick != nullptr) cout << "  - (" << cd.index << ") [" << cd.instanceID << "] " << SDL_JoystickName(cd.joystick) << endl;
		}

		Logger::setColor(ConsoleColor::LIGHTGREY);
	}

	void InputManager::init() {

		for (bool& k : keys) k = false;

		SDL_JoystickEventState(SDL_ENABLE);
		SDL_GameControllerEventState(SDL_ENABLE);

		for (int i = 0; i < SDL_NumJoysticks(); ++i) {
			addController(i);
		}


	}

	void InputManager::update() {

		ButtonMap bm;

		while (SDL_PollEvent(&event) != 0) {

			switch (event.type) {

				case SDL_QUIT:
					GAME->stop();
					break;

				case SDL_KEYDOWN:
					if (!keys[event.key.keysym.scancode]) keys[event.key.keysym.scancode] = true;
					break;

				case SDL_KEYUP:
					keys[event.key.keysym.scancode] = false;
					break;

				case SDL_CONTROLLERDEVICEADDED:
					addController(event.cdevice.which);
					break;

				case SDL_CONTROLLERDEVICEREMOVED:
					removeController(event.cdevice.which);
					break;

				case SDL_CONTROLLERBUTTONDOWN:
					setButton(controllers.at(event.cbutton.which).buttons, event.cbutton.button, true);
					break;

				case SDL_CONTROLLERBUTTONUP:
					setButton(controllers.at(event.cbutton.which).buttons, event.cbutton.button, false);
					break;

				case SDL_CONTROLLERAXISMOTION:
					setAxis(controllers.at(event.cbutton.which).axes, event.caxis.axis, event.caxis.value);
					break;

				case SDL_MOUSEBUTTONDOWN:
					setButton(mouseButtons, event.button.button, true);
					break;

				case SDL_MOUSEBUTTONUP:
					setButton(mouseButtons, event.button.button, false);
					break;

				case SDL_MOUSEMOTION:
					mouse.x = event.motion.x;
					mouse.y = event.motion.y;
					mouse.xrel = event.motion.xrel;
					mouse.yrel = event.motion.yrel;
					break;
			}
		}

		if ((keys[SDL_SCANCODE_LCTRL] && keys[SDL_SCANCODE_Q]) || keys[SDL_SCANCODE_ESCAPE])
			GAME->stop();

		// WINDOW
		if (keys[SDL_SCANCODE_F11]) {
			keys[SDL_SCANCODE_F11] = false;
			GLManager::ToggleFullscreen();
			SDL_Delay(100);
		}
	}

	void InputManager::setButton(ButtonMap& bm, Uint8 button, bool pressed) {
		if (!bm.count(button))
			bm.insert({button, pressed});
		else
			bm[button] = pressed;
	}

	void InputManager::setAxis(AxisMap& am, Uint8 axis, Sint16 value) {
		if (!am.count(axis))
			am.insert({axis, value});
		else
			am[axis] = value;
	}

	bool InputManager::getButton(std::string inputName) {
		if (inputs.count(inputName) == 0) return false;
		ButtonMap bm;
        InputMapping* input = inputs.at(inputName);

        if (keys[input->positiveButton] || keys[input->altPositiveButton]) return true;
        if (mouseButtons[input->mouseButton]) return true;

        if (input->controllerInstance > -1) {
			bm = controllers[input->controllerInstance].buttons;
			if (!bm.count(input->positiveControllerButton))
				bm.insert({input->positiveControllerButton, false});
			else if (bm[input->positiveControllerButton]) return true;
        } else {
			for (auto cm : controllers) {
				ControllerDevice cd = cm.second;
				bm = cd.buttons;
				if (!bm.count(input->positiveControllerButton))
					bm.insert({input->positiveControllerButton, false});
				else if (bm[input->positiveControllerButton]) return true;
			}
        }

        return false;
	}

	double InputManager::getAxis(std::string inputName) {
		if (inputs.count(inputName) == 0) return 0;
		Sint16 value = 0;
		AxisMap am;
		InputMapping* input = inputs.at(inputName);

		if (keys[input->positiveButton] || keys[input->altPositiveButton]) return 1.0d;
		else if (keys[input->negativeButton] || keys[input->altNegativeButton]) return -1.0d;

		if (input->controllerInstance > -1) {
			am = controllers[input->controllerInstance].axes;
			if (!am.count(input->controllerAxis))
				am.insert({input->controllerAxis, 0});
			else value = am[input->controllerAxis];
        } else {
			for (auto cm : controllers) {
				am = cm.second.axes;
				if (!am.count(input->controllerAxis))
					am.insert({input->controllerAxis, 0});
				else value = am[input->controllerAxis];
			}
        }

		double normalizedValue = (double)value / (double)(value >= 0 ? AXIS_VALUE_MAX : -1 * AXIS_VALUE_MIN);
        return (std::abs(normalizedValue) > input->deadZone ? normalizedValue : 0);

	}

	void InputManager::exit() {
		for (auto cm : controllers) {
			if (cm.second.controller != nullptr) SDL_GameControllerClose(cm.second.controller);
			if (cm.second.joystick != nullptr) SDL_JoystickClose(cm.second.joystick);
		}

	}
}
