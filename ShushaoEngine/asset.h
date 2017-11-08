#pragma once

#include <string>

#include "object.h"

using namespace std;

namespace ShushaoEngine {

	class Asset : public Object {

		public:

			Asset();
			Asset(string, string);
			Asset(string);

			bool Load(string);

		protected:

			string basename(string);

		private:
	};

}
