#pragma once

#include <GL/glew.h>
#include <string>
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

	struct Attenuation {
		GLfloat constant;
		GLfloat linear;
		GLfloat quadratic;
	};

	struct UniformLight {
		glm::vec3 position;
		glm::vec3 direction;
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
		GLfloat constant;
		GLfloat linear;
		GLfloat quadratic;
		GLfloat cutoff;
	};

	class Light : public Component {

		public:

			Light();

			bool enabled;

			LightType type = LightType::POINT;

			glm::vec3 direction;
			Color ambient = Color::white;
			Color diffuse = Color::white;
			Color specular = Color::white;
			Attenuation attenuation {1.0f, 1.0f, 1.0f};
			float cutoff;

			std::string GetTypeDesc();
			UniformLight GetUniform();

		protected:

			void Update();
	};

}
