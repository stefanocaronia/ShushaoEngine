#pragma once

#include <string>

#include "object.h"

namespace ShushaoEngine {

	class Service : public Object{

		public:

			Service();
			virtual ~Service();

			bool active;

			virtual void init();
			virtual void update();
			virtual void exit();

		protected:

		private:
	};

}
