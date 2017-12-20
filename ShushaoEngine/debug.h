#pragma once

#include <map>

#include "logger.h"

using namespace std;

namespace ShushaoEngine {

	enum GridMode {
		ORTHOGRAFIC,
		PERSPECTIVE
	};



	class Debug {

		public:

			static bool enabled;
			static bool gridEnabled;
			static GridMode debugGridMode;
			static DebugLevel level;
			static Logger Log;

	};

}
