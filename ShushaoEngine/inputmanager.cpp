#include "inputmanager.h"

#include <string>
#include <iostream>

#include "setime.h"

using namespace std;

namespace ShushaoEngine {

	InputManager::InputManager() {
		cout << " - Contstructor di InputManager" << this << endl;
	}

	InputManager::~InputManager() {
		cout << " - Destructor di InputManager" << endl;
		//dtor
	}

	void InputManager::init() {
		//cout << "InputManager init" << endl;
	}

	void InputManager::update() {
		// todo
	}

	void InputManager::exit() {
		cout << " - InputManager exit" << endl;
	}
}
