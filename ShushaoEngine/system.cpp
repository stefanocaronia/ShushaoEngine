#include "system.h"
#include "inputmanager.h"
#include "service.h"

namespace ShushaoEngine {

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


	vector<Service*> System::Services;

	//Service* System::Input = System::AddService<InputManager>();
	Service& System::Input = System::AddService<InputManager>();

}
