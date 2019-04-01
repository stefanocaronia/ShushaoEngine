#pragma once

#include <GL/glew.h>
#include <string>
#include "component.h"
#include "color.h"

namespace se {

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

			enum class Type {
				SPOT,
				DIRECTIONAL,
				POINT,
				RECTANGLE,
				DISC
			};

			virtual void setup() { name = "Light"; }

			bool enabled;

			Light::Type type = Light::Type::POINT;

			glm::vec3 direction;
			Color ambient = color::white;
			Color diffuse = color::white;
			Color specular = color::white;
			Attenuation attenuation {1.0f, 1.0f, 1.0f};
			float cutoff;

			std::string GetTypeDesc();
			UniformLight GetUniform();

		protected:

			void Update();
			void Render();
	};

}
