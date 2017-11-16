#include "system.h"
#include "inputmanager.h"
#include "service.h"
#include "debug.h"

#include <iostream>

namespace ShushaoEngine {

	using namespace std;

	void System::init() {
		for (Service* s : Services) {
			s->init();
		}
	}

	void System::update() {
		for (Service* s : Services) {
			s->update();
		}
	}

	void System::exit() {
		for (Service* s : Services) {
			s->exit();
		}

		Clear();
	}

	void System::Clear() {
		for (Service* s : Services) {
			delete(s);
		}
		Services.clear();
	}

	void System::ListServices() {
		Debug::SetColor(YELLOW);
		cout << " System" << endl;
		Debug::SetColor(DARKYELLOW);
		for (Service* s : Services) {
			cout << " " << (char)192 << (char)196;
			cout << " " << s->name << (s->active ? "+": "");
		}

        cout << endl;

        Debug::SetColor(WHITE);
	}

	vector<Service*> System::Services;

	//Service* System::Input = System::AddService<InputManager>();
	Service& System::Input = System::AddService<InputManager>();

}
