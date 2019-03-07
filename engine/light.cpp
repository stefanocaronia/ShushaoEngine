#include "light.h"

namespace se {

	Light::Light() {
	}

	std::string Light::GetTypeDesc() {
		switch (type) {
			case LightType::SPOT: return "Spot"; break;
			case LightType::DIRECTIONAL: return "Directional"; break;
			case LightType::POINT: return "Point"; break;
			case LightType::RECTANGLE: return "Rectangle"; break;
			case LightType::DISC: return "Disc"; break;
		}
		return "NP";
	}

} // namespace se
