#pragma once

#include <string>

using namespace std;

namespace ShushaoEngine {

	class System;

	class Service {

		public:

			Service();
			virtual ~Service();

			string name;

			virtual void init();
			virtual void update();
			virtual void exit();

		protected:

		private:
	};

}
