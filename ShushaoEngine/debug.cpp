#include <string>
#include <sstream>

#include "utility.h"
#include "debug.h"
#include "setime.h"
#include "config.h"

namespace ShushaoEngine {

	using namespace std;

	void Debug::Log(string message, const char* funcname, const char* file, int line) {
		if (!enable) return;
		string fname = Utility::basename(file);
		cout << "[" << Time::Clock() <<"] " << fname << "::" << funcname << "(" << line << ") " << message << endl;
	}

	void Debug::Log(const ostringstream& message, const char* funcname, const char* file, int line) {
		if (!enable) return;
		string fname = Utility::basename(file);
		cout << "[" << Time::Clock() <<"] " << fname << "::" << funcname << "(" << line << ") " << message.str() << endl;
	}

	bool Debug::enable = Config::debug;

}
