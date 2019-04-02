#pragma once

#include "component.h"

namespace se {

	class Program : public Component {
		public:

			virtual void setup() { name = "Program"; }
			~Program();

		protected:


		private:
	};

}
