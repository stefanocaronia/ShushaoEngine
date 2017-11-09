#include "service.h"

namespace ShushaoEngine {

	class InputManager : public Service {

		public:
			InputManager();
			~InputManager();

			void init();
			void update();
			void exit();

		protected:

		private:
	};

}
