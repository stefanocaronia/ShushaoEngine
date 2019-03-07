#pragma once

#include <map>
#include "component.h"
#include "color.h"

namespace se {

	enum class LightType {
		SPOT,
		DIRECTIONAL,
		POINT,
		RECTANGLE,
		DISC
	};
	class Light : public Component {

		public:

			Light();

			bool enabled;  // Makes the rendered 3D object visible if enabled.

			LightType type = LightType::POINT;
			Color color = Color::white;

			std::string GetTypeDesc();

		protected:

			virtual void Awake() {};
			virtual void Update() {};
			virtual void Render() {};
			virtual void OnDestroy() {};

		private:
	};

}
