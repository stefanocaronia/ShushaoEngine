#include <string>
#include <sstream>
#include <ostream>
#include <fstream>

#include "utility.h"
#include "debug.h"
#include "setime.h"
#include "config.h"

namespace ShushaoEngine {

	using namespace std;

	map <DebugLevel, string> DebugLevelName = {
		{INFO, "Info"},
		{WARNING, "Warning"},
		{ERROR, "Error"}
	};

	void Debug::Log(DebugLevel level, string message, string sender) {
		if (!Enabled || level < Level) return;
		if (sender != "") sender = "<" + sender + "> ";

		ostringstream buildmex;
		buildmex << Time::Clock() << " [" << DebugLevelName[level] << "]"<< " " << sender << message << endl;

		cout << buildmex.str();

		ios_base::openmode mode = ios_base::out;
		if (logStarted) mode = mode | ios_base::app;

		debugfile.open("debug.log", mode);

		debugfile << buildmex.str();
		debugfile.close();

		logStarted = true;
	}

	void Debug::Log(DebugLevel level, const ostringstream& message, string sender) {
		Log(level, message.str(), sender);
	}

	bool Debug::logStarted = false;
	bool Debug::Enabled = Config::debug;
	GridMode Debug::DebugGridMode = GridMode::ORTHOGRAFIC;
	ofstream Debug::debugfile;
	DebugLevel Debug::Level = DebugLevel::INFO;

}
