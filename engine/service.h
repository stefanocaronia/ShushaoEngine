#pragma once

#include <string>

#include "object.h"

namespace ShushaoEngine {

	class Service : public Object {

		public:

			Service();
			virtual ~Service();

			bool active;

			virtual void Init();
			virtual void Update();
			virtual void Exit();

		protected:

		private:
	};

}
