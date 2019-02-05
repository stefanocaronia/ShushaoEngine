#include <iostream>

#include "system.h"
#include "service.h"
#include "debug.h"

namespace ShushaoEngine {

	using namespace std;

	void System::init() {
		for (Service* s : Services) {
			s->Init();
		}
	}

	void System::update() {
		for (Service* s : Services) {
			s->Update();
		}
	}

	void System::exit() {
		for (Service* s : Services) {
			s->Exit();
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
		Logger::setColor(ConsoleColor::YELLOW);
		cout << " System" << endl;
		Logger::setColor(ConsoleColor::DARKYELLOW);
		for (Service* s : Services) {
			cout << " " << (char)192 << (char)196;
			cout << " " << s->name << (s->active ? "+": "");
		}

        cout << endl;

        Logger::setColor(ConsoleColor::WHITE);
	}

	vector<Service*> System::Services;

	//Service* System::Input = System::AddService<InputManager>();
	//InputManager& System::Input = System::AddService<InputManager>();
	//Cycle* System::Game;

}
