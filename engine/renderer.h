#pragma once

#include "component.h"

namespace se {

	class Renderer : public Component {

		public:

			Renderer();

			bool enabled;  // Makes the rendered 3D object visible if enabled.

			bool isVisible; //Is this renderer visible in any camera? (Read Only)
			int sortingLayerID = 0; //Unique ID of the Renderer's sorting layer.
			int sortingOrder = 0; //Renderer's order within a sorting layer.

		protected:

			// messages

			void OnBecameInvisible(); // OnBecameInvisible is called when the object is no longer visible by any camera.
			void OnBecameVisible(); // OnBecameVisible is called when the object became visible by any camera.

		private:
	};

}
