#pragma once

#include <map>
#include <string>
#include <vector>

#include "service.h"
#include "gllibs.h"

namespace ShushaoEngine {

	enum class InputType {
		BUTTON,
		MOUSE_MOVEMENT,
		AXIS,
	};

	struct InputMapping {

		std::string name;

		SDL_Keycode positiveButton;
		SDL_Keycode negativeButton;

		SDL_Keycode altPositiveButton;
		SDL_Keycode altNegativeButton;

		float deadZone = 0.2f;

		/*float gravity;
		float sensitivity;
		bool snap;
		bool invert;*/

		InputType type;

		SDL_JoystickID controllerInstance = -1;
		SDL_GameControllerAxis controllerAxis;
		/*
			SDL_CONTROLLER_AXIS_INVALID
			SDL_CONTROLLER_AXIS_LEFTX
			SDL_CONTROLLER_AXIS_LEFTY
			SDL_CONTROLLER_AXIS_RIGHTX
			SDL_CONTROLLER_AXIS_RIGHTY
			SDL_CONTROLLER_AXIS_TRIGGERLEFT
			SDL_CONTROLLER_AXIS_TRIGGERRIGHT
			SDL_CONTROLLER_AXIS_MAX
		*/
		SDL_GameControllerButton positiveControllerButton;
		SDL_GameControllerButton negativeControllerButton;
		/*
			SDL_CONTROLLER_BUTTON_INVALID
			SDL_CONTROLLER_BUTTON_A
			SDL_CONTROLLER_BUTTON_B
			SDL_CONTROLLER_BUTTON_X
			SDL_CONTROLLER_BUTTON_Y
			SDL_CONTROLLER_BUTTON_BACK
			SDL_CONTROLLER_BUTTON_GUIDE
			SDL_CONTROLLER_BUTTON_START
			SDL_CONTROLLER_BUTTON_LEFTSTICK
			SDL_CONTROLLER_BUTTON_RIGHTSTICK
			SDL_CONTROLLER_BUTTON_LEFTSHOULDER
			SDL_CONTROLLER_BUTTON_RIGHTSHOULDER
			SDL_CONTROLLER_BUTTON_DPAD_UP
			SDL_CONTROLLER_BUTTON_DPAD_DOWN
			SDL_CONTROLLER_BUTTON_DPAD_LEFT
			SDL_CONTROLLER_BUTTON_DPAD_RIGHT
			SDL_CONTROLLER_BUTTON_MAX
		*/

		Uint8 mouseButton;
		/*
			SDL_BUTTON_LEFT
			SDL_BUTTON_MIDDLE
			SDL_BUTTON_RIGHT
			SDL_BUTTON_X1
			SDL_BUTTON_X2
		*/
	};

	typedef std::map<Uint8, bool> ButtonMap;
	typedef std::map<Uint8, Sint16> AxisMap;

	struct ControllerDevice {
		int index;
		SDL_JoystickID instanceID;
		SDL_Joystick* joystick;
		SDL_GameController* controller;
		ButtonMap buttons;
		AxisMap axes;
	};

	class InputManager : public Service {

		public:
			InputManager();
			~InputManager();

			InputMapping* addMapping(std::string);
			InputMapping* getMapping(std::string);

			bool getButton(std::string);
			double getAxis(std::string);
			void addController(int);
			void removeController(int);
			void printActiveControllers();
			void setButton(ButtonMap&, Uint8, bool);
			void setAxis(AxisMap&, Uint8, Sint16);

			struct mouseState {
				Sint32 x;
				Sint32 y;
				Sint32 xrel;
				Sint32 yrel;
			} mouse;



		protected:

			void init();
			void update();
			void exit();

		private:

			const Sint16 AXIS_VALUE_MIN = -32768;
			const Sint16 AXIS_VALUE_MAX = 32767;

			/*const ButtonMap CONTROLLER_BUTTONS = {
				{ SDL_CONTROLLER_BUTTON_A, false},
				{ SDL_CONTROLLER_BUTTON_B, false},
				{ SDL_CONTROLLER_BUTTON_X, false},
				{ SDL_CONTROLLER_BUTTON_Y, false},
				{ SDL_CONTROLLER_BUTTON_BACK, false},
				{ SDL_CONTROLLER_BUTTON_GUIDE, false},
				{ SDL_CONTROLLER_BUTTON_START, false},
				{ SDL_CONTROLLER_BUTTON_LEFTSTICK, false},
				{ SDL_CONTROLLER_BUTTON_RIGHTSTICK, false},
				{ SDL_CONTROLLER_BUTTON_LEFTSHOULDER, false},
				{ SDL_CONTROLLER_BUTTON_RIGHTSHOULDER, false},
				{ SDL_CONTROLLER_BUTTON_DPAD_UP, false},
				{ SDL_CONTROLLER_BUTTON_DPAD_DOWN, false},
				{ SDL_CONTROLLER_BUTTON_DPAD_LEFT, false},
				{ SDL_CONTROLLER_BUTTON_DPAD_RIGHT, false}
			};*/

			bool keys[350];
			ButtonMap mouseButtons;

			SDL_Event event;

			std::map<SDL_JoystickID, ControllerDevice> controllers;

			std::map<std::string, InputMapping*> inputs;
	};

}
