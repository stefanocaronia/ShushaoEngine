#pragma once

#define CONSOLE_COLORS

#ifdef CONSOLE_COLORS
#include <windows.h>
#undef ERROR
#undef SendMessage
#endif

#include <iostream>
#include <sstream>
#include <fstream>
#include <map>

#include "stime.h"
#include "utility.h"

#define SOURCE util::basename(__FILE__) + "::" + __FUNCTION__ + ":" + util::toString(__LINE__) + ""
#define LOG(MESSAGE) Debug::Log(SOURCE) << MESSAGE << std::endl;

namespace se {

	using namespace std;

	enum DebugLevel {
		INFO,
		WARNING,
		ERROR
	};

	enum ConsoleColor {
		ZERO,
		DARKBLUE,
		DARKGREEN,
		DARKCYAN,
		DARKRED,
		DARKPURPLE,
		DARKYELLOW,
		LIGHTGREY,
		GREY,
		BLUE,
		GREEN,
		CYAN,
		RED,
		PINK,
		YELLOW,
		WHITE
	};

	class Logger {

			std::ostringstream stream;
			DebugLevel streamLevel = DebugLevel::INFO;
			bool logStarted = false;
			ofstream debugfile;
			string sender = "";
			string debugFilename = "debug.log";

		public:

			Logger(DebugLevel level_);

			DebugLevel level;
			bool enabled = false;

			Logger& operator()(DebugLevel l);
			Logger& operator()(DebugLevel l, string s) ;
			Logger& operator()(string s) ;

			template<typename T>
			Logger& operator<<(T&& value) {
				if (streamLevel < level) return *this;
				stream << value;
				return *this;
			}

			Logger& operator<<(std::ostream& (*os)(std::ostream&));

			static void setColor(ConsoleColor);
	};

}
