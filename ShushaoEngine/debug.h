#pragma once

#define CONSOLE_COLORS

#ifdef CONSOLE_COLORS
#include <windows.h>
#undef ERROR
#endif

#include <iostream>
#include <sstream>
#include <fstream>
#include <map>

#include "setime.h"
#include "utility.h"

#define SOURCE Utility::basename(__FILE__) + "::" + __FUNCTION__ + ":" + Utility::toString(__LINE__) + ""
#define LOG(LEVEL, MESSAGE) Debug::Log(LEVEL, MESSAGE, SOURCE);

using namespace std;

namespace ShushaoEngine {

	enum DebugLevel {
		INFO,
		WARNING,
		ERROR
	};

	enum GridMode {
		ORTHOGRAFIC,
		PERSPECTIVE
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

	class Debug {

		public:

			static bool Enabled;
			static DebugLevel Level;
			static GridMode DebugGridMode;

			static void SetColor(ConsoleColor);

			static bool logStarted;
			static ofstream debugfile;

			static void Log(DebugLevel level, string message, string sender = "");
			static void Log(DebugLevel level, const ostringstream& message, string sender = "");

		protected:

		private:
	};

}
