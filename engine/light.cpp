#include "light.h"
#include "transform.h"
#include "entity.h"
#include "design.h"

namespace se {

	using namespace glm;

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

	UniformLight Light::GetUniform() {
		return {
			entity->transform->position,
			entity->transform->forward,
			ambient.rgb(),
			diffuse.rgb(),
			specular.rgb(),
			attenuation.constant,
			attenuation.linear,
			attenuation.quadratic
		};
	}

	void Light::Update() {
		direction = entity->transform->forward;
	}

	void Light::Render() {
		if (Debug::enabled) {
			Design::DrawVector(transform->position, direction, Color::red, 1, true);
		}

	}

} // namespace se
