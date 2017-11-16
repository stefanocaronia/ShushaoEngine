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
		{INFO, "INFO"},
		{WARNING, "WARNING"},
		{ERROR, "ERROR"}
	};

	void Debug::Log(DebugLevel level, string message, string sender) {
		if (!Enabled || level < Level) return;
		if (sender != "") sender = "<" + sender + "> ";

		if (level == INFO ) SetColor(LIGHTGREY);
		else if (level == WARNING ) SetColor(YELLOW);
		else if (level == ERROR ) SetColor(RED);

		ostringstream buildmex;
		buildmex << Time::Clock() << " [" << DebugLevelName[level] << "]"<< " " << sender << message << endl;

		cout << buildmex.str();

		ios_base::openmode mode = ios_base::out;
		if (logStarted) mode = mode | ios_base::app;

		debugfile.open("debug.log", mode);

		debugfile << buildmex.str();
		debugfile.close();

		logStarted = true;

		SetColor(LIGHTGREY);
	}

	void Debug::Log(DebugLevel level, const ostringstream& message, string sender) {
		Log(level, message.str(), sender);
	}

	void Debug::SetColor(ConsoleColor color) {
		#ifdef CONSOLE_COLORS
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
		#endif
	}

	bool Debug::logStarted = false;
	bool Debug::Enabled = Config::debug;
	GridMode Debug::DebugGridMode = GridMode::ORTHOGRAFIC;
	ofstream Debug::debugfile;
	DebugLevel Debug::Level = DebugLevel::INFO;

}
