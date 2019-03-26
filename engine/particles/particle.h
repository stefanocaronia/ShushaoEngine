#pragma once

#include <glm/glm.hpp>

#include "../color.h"

namespace se {

	class Particle {

		public:

			float angularVelocity; // angular velocity of the particle.
			glm::vec3 angularVelocity3D; // The 3D angular velocity of the particle.
			glm::vec3 animatedVelocity; // The animated velocity of the particle.
			glm::vec3 axisOfRotation; // Mesh particles will rotate around this axis.
			glm::vec3 position; // The position of the particle.
			unsigned int randomSeed; // The random seed of the particle.
			float remainingLifetime; // The remaining lifetime of the particle.
			float rotation; // The rotation of the particle.
			glm::vec3 rotation3D; // The 3D rotation of the particle.
			Color startColor; // The initial color of the particle. The current color of the particle is calculated procedurally based on this value and the active color modules.
			float startLifetime; // The starting lifetime of the particle.
			float startSize; // The initial size of the particle. The current size of the particle is calculated procedurally based on this value and the active size modules.
			glm::vec3 startSize3D; // The initial 3D size of the particle. The current size of the particle is calculated procedurally based on this value and the active size modules.
			glm::vec3 totalVelocity; // The total velocity of the particle.
			glm::vec3 velocity; // The velocity of the particle.

			Color GetCurrentColor(); //	Calculate the current color of the particle by applying the relevant curves to its startColor property.
			float GetCurrentSize(); // Calculate the current size of the particle by applying the relevant curves to its startSize property.
			glm::vec3 GetCurrentSize3D(); //	Calculate the current 3D size of the particle by applying the relevant curves to its startSize3D property.

	};

}
