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

	Logger::Logger(DebugLevel level_) {
		level = level_;
	}

	Logger& Logger::operator()(DebugLevel debugLevel_) {
		streamLevel = debugLevel_;
		return *this;
	}


	Logger& Logger::operator()(DebugLevel debugLevel_, string sender_) {
		streamLevel = debugLevel_;
		sender = sender_;
		return *this;
	}

	Logger& Logger::operator()(string sender_) {
		sender = sender_;
		return *this;
	}

	Logger& Logger::operator<<(std::ostream& (*os)(std::ostream&)) {

		if (streamLevel < level) return *this;

		if (streamLevel == INFO ) setColor(ConsoleColor::LIGHTGREY);
		else if (streamLevel == WARNING ) setColor(ConsoleColor::YELLOW);
		else if (streamLevel == ERROR ) setColor(ConsoleColor::RED);

		if (sender != "") sender = "<" + sender + "> ";

		ostringstream buildmex;
		buildmex << Time::Clock() << " [" << DebugLevelName[streamLevel] << "] " << sender << stream.str() << os;

		cout << buildmex.str();

		ios_base::openmode mode = ios_base::out;
		if (logStarted) mode = mode | ios_base::app;

		debugfile.open(debugFilename, mode);
		debugfile << buildmex.str();
		debugfile.close();

		logStarted = true;

		setColor(ConsoleColor::LIGHTGREY);
		stream.str("");
		streamLevel = DebugLevel::INFO;
		sender = "";

		return *this;
	}

	void Logger::setColor(ConsoleColor color) {
		#ifdef CONSOLE_COLORS
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
		#endif
	}

}
