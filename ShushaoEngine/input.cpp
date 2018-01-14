#include <string>
#include <iostream>

#include "input.h"
#include "gllibs.h"
#include "cycle.h"
#include "setime.h"
#include "glmanager.h"
#include "system.h"
#include "debug.h"

using namespace std;

namespace ShushaoEngine {

	InputMapping* Input::addMapping(string name_) {
		InputMapping* input = new InputMapping();
		input->name = name_;
		inputs[name_] = input;
		return input;
	}

	InputMapping* Input::getMapping(string name_) {
		return inputs[name_];
	}

	void Input::addController(int index) {
		if (SDL_IsGameController(index)) {
			SDL_GameController* gc = SDL_GameControllerOpen(index);
			SDL_JoystickID id = SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(gc));
			controllers.insert({id, {index, id, nullptr, gc }});
			cout << controllers[id].toString() << endl;
		} else {
			SDL_Joystick* j = SDL_JoystickOpen(index);
			SDL_JoystickID id = SDL_JoystickInstanceID(j);
			controllers.insert({id, { index, id, j, nullptr }});
			cout << controllers[id].toString() << endl;
		}
	}

	void Input::removeController(int instance) {
		SDL_GameController* gc = controllers.at(instance).controller;
		SDL_GameControllerClose(gc);
		cout << "Disconnected: " << controllers.at(instance).toString() << endl;
		controllers.erase(instance);
	}

	void Input::printActiveControllers() {
		Logger::setColor(ConsoleColor::RED);
		cout << " InputManager Active Controllers:" << endl;
		for (auto cm : controllers) {
			Logger::setColor(ConsoleColor::RED);
			cout << "  - " << cm.second.toString() << endl;
		}
		Logger::setColor(ConsoleColor::LIGHTGREY);
	}

	void Input::init() {

		for (bool& k : keys) k = false;

		SDL_JoystickEventState(SDL_ENABLE);
		SDL_GameControllerEventState(SDL_ENABLE);

		for (int i = 0; i < SDL_NumJoysticks(); ++i) {
			addController(i);
		}
	}

	void Input::update() {

		// clear temp events
		mouseMoved = false;
		changedKeys.clear();
		changedMouseButtons.clear();
		changedButtons.clear();

		if (!controllers.empty()) {
			for (auto cm : controllers) {
				cm.second.changedButtons.clear();
			}
		}

		while (SDL_PollEvent(&event) != 0) {
			switch (event.type) {

				case SDL_QUIT:
					GAME->stop();
					break;

				case SDL_KEYDOWN:
					if (!keys[event.key.keysym.scancode]) {
						keys[event.key.keysym.scancode] = true;
                        changedKeys[event.key.keysym.scancode] = true;
					}
					break;

				case SDL_KEYUP:
					keys[event.key.keysym.scancode] = false;
					changedKeys[event.key.keysym.scancode] = false;
					break;

				case SDL_CONTROLLERDEVICEADDED:
					addController(event.cdevice.which);
					break;

				case SDL_CONTROLLERDEVICEREMOVED:
					removeController(event.cdevice.which);
					break;

				case SDL_CONTROLLERBUTTONDOWN:
					if (!controllers.empty()) {
						controllers[event.cbutton.which].buttons[event.cbutton.button] = true;
						controllers[event.cbutton.which].changedButtons[event.cbutton.button] = true;
					}
					buttons[event.cbutton.button] = true;
					changedButtons[event.cbutton.button] = true;
					break;

				case SDL_CONTROLLERBUTTONUP:
					if (!controllers.empty()) {
						controllers[event.cbutton.which].buttons[event.cbutton.button] = false;
						controllers[event.cbutton.which].changedButtons[event.cbutton.button] = false;
					}
					buttons[event.cbutton.button] = false;
					changedButtons[event.cbutton.button] = false;
					break;

				case SDL_CONTROLLERAXISMOTION:
					if (!controllers.empty())
						controllers[event.cbutton.which].axes[event.caxis.axis] = event.caxis.value;
					break;

				case SDL_MOUSEBUTTONDOWN:
					mouseButtons[event.button.button] = true;
					changedMouseButtons[event.button.button] = true;
					break;

				case SDL_MOUSEBUTTONUP:
					mouseButtons[event.button.button] = false;
					changedMouseButtons[event.button.button] = false;
					break;

				case SDL_MOUSEMOTION:
					mouseMoved = true;
					mousePosition.x = event.motion.x;
					mousePosition.y = event.motion.y;
					mousePosition.xrel = event.motion.xrel;
					mousePosition.yrel = event.motion.yrel;
					break;
			}
		}
	}

	bool Input::getButton(std::string inputName) {
		if (inputs.count(inputName) == 0) return false;
        InputMapping* input = inputs.at(inputName);
        if (input->type != InputType::BUTTON)
			return false;

        if (keys[input->positiveButton] || keys[input->altPositiveButton])
			return true;

        if (mouseButtons[input->mouseButton])
			return true;

		if (input->controllerInstance > -1 && !controllers.empty()) {
			ButtonMap bm = controllers[input->controllerInstance].buttons;
			if (!bm.count(input->positiveControllerButton))
				bm[input->positiveControllerButton] = false;
			else
				return bm[input->positiveControllerButton];
		} else {
			if (!buttons.count(input->positiveControllerButton))
				buttons[input->positiveControllerButton] = false;
			else
				return buttons[input->positiveControllerButton];
		}

        return false;
	}

	bool Input::getButtonDown(std::string inputName) {
		if (inputs.count(inputName) == 0) return false;
		InputMapping* input = inputs.at(inputName);
		if (input->type != InputType::BUTTON)
			return false;

		if (changedKeys[input->positiveButton] || changedKeys[input->altPositiveButton])
			return true;
        if (changedMouseButtons[input->mouseButton])
			return true;

		if (input->controllerInstance > -1 && !controllers.empty()) {
			ButtonMap bm = controllers[input->controllerInstance].changedButtons;
			if (bm.count(input->positiveControllerButton))
				return bm[input->positiveControllerButton];
		} else if (changedButtons.count(input->positiveControllerButton)) {
			return changedButtons[input->positiveControllerButton];
		}

		return false;
	}

	bool Input::getButtonUp(std::string inputName) {
		if (inputs.count(inputName) == 0) return false;
		InputMapping* input = inputs.at(inputName);
		if (input->type != InputType::BUTTON)
			return false;

		if (!changedKeys[input->positiveButton] || !changedKeys[input->altPositiveButton])
			return true;
        if (!changedMouseButtons[input->mouseButton])
			return true;

		if (input->controllerInstance > -1 && !controllers.empty()) {
			ButtonMap bm = controllers[input->controllerInstance].changedButtons;
			if (bm.count(input->positiveControllerButton))
				return !bm[input->positiveControllerButton];
		} else if (changedButtons.count(input->positiveControllerButton)) {
			return !changedButtons[input->positiveControllerButton];
		}

		return false;
	}

	double Input::getAxis(std::string inputName) {
		if (inputs.count(inputName) == 0) return 0;
		InputMapping* input = inputs.at(inputName);

		if (input->type == InputType::BUTTON)
			return 0;

		if (input->type == InputType::MOUSE) {
			if (!mouseMoved) return 0;
			if (input->mouseAxis == Axis::X) {
				return (double)mousePosition.xrel * input->sensitivity;
			} else if (input->mouseAxis == Axis::Y) {
				return (double)mousePosition.yrel * input->sensitivity;
			}
		}

		Sint16 value = 0;
		double normalizedValue;
		AxisMap am;

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

		normalizedValue = (double)value / (double)(value >= 0 ? AXIS_VALUE_MAX : -1 * AXIS_VALUE_MIN);
        return (std::abs(normalizedValue) > input->deadZone ? normalizedValue : 0);
	}

	bool Input::getKey(int key) {
		return keys[key];
	}

	bool Input::getKeyDown(int key) {
		return (changedKeys.count(key) && changedKeys[key]);
	}

	bool Input::getKeyUp(int key) {
		return (changedKeys.count(key) && !changedKeys[key]);
	}

	bool Input::getMouseButton(int button) {
		return mouseButtons.count(button) && mouseButtons[button];
	}

	bool Input::getMouseButtonDown(int button) {
		return (changedMouseButtons.count(button) && changedMouseButtons[button]);
	}

	bool Input::getMouseButtonUp(int button) {
		return (changedMouseButtons.count(button) && !changedMouseButtons[button]);
	}

	void Input::exit() {
		for (auto cm : controllers) {
			if (cm.second.controller != nullptr) SDL_GameControllerClose(cm.second.controller);
			if (cm.second.joystick != nullptr) SDL_JoystickClose(cm.second.joystick);
		}

		for (auto const& m : inputs) {
			delete(m.second);
		}
		inputs.clear();
	}

	// initialization
	SDL_Event Input::event;
	bool Input::mouseMoved = false;
	MouseState Input::mousePosition;
	std::map<std::string, InputMapping*>  Input::inputs;
	std::map<SDL_JoystickID, ControllerDevice>  Input::controllers;
	bool Input::keys[350];
	ButtonMap Input::mouseButtons;
	ButtonMap Input::changedKeys;
	ButtonMap Input::changedMouseButtons;
	ButtonMap Input::buttons;
	ButtonMap Input::changedButtons;
}