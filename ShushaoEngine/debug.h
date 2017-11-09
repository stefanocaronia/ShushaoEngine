#pragma once

#include <iostream>
#include <sstream>

#include "setime.h"

#define LOG(MESSAGE) Debug::Log(MESSAGE, __FUNCTION__, __FILE__, __LINE__);

using namespace std;

namespace ShushaoEngine {

	class Debug {

		public:

			static bool enable;

			static void Log(string message, const char* funcname = __FUNCTION__, const char* file = __FILE__, int line = __LINE__);
			static void Log(const ostringstream& message, const char* funcname = __FUNCTION__, const char* file = __FILE__, int line = __LINE__);

		protected:

		private:
	};

}
