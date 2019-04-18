#pragma once

#include "pch/sdl.h"
#include "pch/std.h"

    namespace se {

    enum class InputType {
        BUTTON,
        MOUSE,
        AXIS,
    };

    enum class Axis {
        X,
        Y
    };

    struct InputMapping {
        std::string name;

        SDL_Keycode positiveButton;
        SDL_Keycode negativeButton;

        SDL_Keycode altPositiveButton;
        SDL_Keycode altNegativeButton;

        float deadZone = 0.2f;
        float sensitivity = 1.0f;

        /*float gravity;

		bool snap;
		bool invert;*/

        InputType type = InputType::BUTTON;

        Axis mouseAxis = Axis::X;

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

    typedef std::map<int, bool> ButtonMap;
    typedef std::map<int, Sint16> AxisMap;

    struct ControllerDevice {
        int index;
        SDL_JoystickID instanceID;
        SDL_Joystick* joystick;
        SDL_GameController* controller;
        ButtonMap buttons;
        ButtonMap changedButtons;
        AxisMap axes;

        std::string toString() {
            if (controller != nullptr)
                return "Controller (" + ts(index) + ") [" + ts(instanceID) + "] " + SDL_GameControllerName(controller);
            else if (joystick != nullptr)
                return "Joystick (" + ts(index) + ") [" + ts(instanceID) + "] " + SDL_JoystickName(joystick);
            return "";
        }
    };

    struct MouseState {
        Sint32 x;
        Sint32 y;
        Sint32 xrel;
        Sint32 yrel;
    };

    class Input {
    public:
        static InputMapping* addMapping(std::string);
        static InputMapping* getMapping(std::string);

        // virtual mapping
        static bool getButton(std::string);
        static bool getButtonDown(std::string);
        static bool getButtonUp(std::string);
        static double getAxis(std::string);

        // direct get
        static bool getKey(int);
        static bool getKeyDown(int);
        static bool getKeyUp(int);
        static bool getMouseButton(int);
        static bool getMouseButtonDown(int);
        static bool getMouseButtonUp(int);

        // set
        static void addController(int);
        static void removeController(int);
        static void printActiveControllers();

        static MouseState mousePosition;
        static bool mouseMoved;

        static void init();
        static void update();
        static void exit();

    private:
        static SDL_Event event;

        static const Sint16 AXIS_VALUE_MIN = -32768;
        static const Sint16 AXIS_VALUE_MAX = 32767;

        static bool keys[350];
        static ButtonMap mouseButtons;
        static ButtonMap changedKeys;
        static ButtonMap changedMouseButtons;

        // all controllers
        static ButtonMap buttons;
        static ButtonMap changedButtons;

        static std::map<SDL_JoystickID, ControllerDevice> controllers;
        static std::map<std::string, InputMapping*> inputs;
    };
}  // namespace se
