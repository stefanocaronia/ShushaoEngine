#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "../renderer.h"
#include "../texture.h"
#include "../material.h"
#include "../color.h"
#include "../vao.h"
#include "../playable.h"
#include "modules.h"

namespace se {

	struct Particle {

			Particle()
				: position(0)
				, velocity(0)
				, color(0)
				, rotation(0)
				, age(0)
				, lifetime(0)
			{}

			glm::vec3 position;
			glm::vec3 velocity;
			Color color;
			float rotation;
			glm::vec2 size;
			float age;
			float lifetime;

			void copy(Particle other) {
				position = other.position;
				velocity = other.velocity;
				color = other.color;
				rotation = other.rotation;
				size = other.size;
				age = other.age;
				lifetime = other.lifetime;
			}

	};

	class ParticleSystem : public Renderer, public Playable {

		public:

			virtual void setup();
			~ParticleSystem();
			bool isReady();

			float startDelay; // Start delay in seconds.
			float startLifetime; // The total lifetime in seconds that each new particle will have.
			float startSpeed; // The initial speed of particles when emitted.
			glm::vec2 startSize; // The initial size of particles when emitted.
			float startRotation; // The initial rotation of particles when emitted.
			Color startColor; // The initial color of particles when emitted.

			unsigned int maxParticles; // The maximum number of particles to emit.
			bool playOnAwake; // If set to true, the Particle System will automatically start playing on startup.
			float simulationSpeed; // Override the default playback speed of the Particle System.

			//void* stopAction;	Select whether to Disable or Destroy the GameObject, or to call the OnParticleSystemStopped script Callback, when the Particle System is stopped and all particles have died.
			bool useUnscaledTime; // When true, use the unscaled delta time to simulate the Particle System. Otherwise, use the scaled delta time.

			Texture* texture = nullptr;
			Material* material = nullptr;
			Vao* VAO = nullptr;

			EmissionModule emission; // Script interface for the Particle System emission module.
			ShapeModule shape; // Script interface for the Particle System Shape module.
			ColorOverLifetimeModule colorOverLifetime; // Script interface for the Particle System color over lifetime module.
			ForceOverLifetimeModule forceOverLifetime; // Script interface for the Particle System force over lifetime module.
			RotationBySpeedModule rotationBySpeedModule; // rotationBySpeed; // Script interface for the Particle System Rotation by Speed module.
			RotationOverLifetimeModule rotationOverLifetimeModule; // rotationOverLifetime; // Script interface for the Particle System Rotation over Lifetime module.
			SizeBySpeedModule sizeBySpeed; // Script interface for the Particle System Size by Speed module.
			SizeOverLifetimeModule sizeOverLifetime; // Script interface for the Particle System Size over Lifetime module.
			VelocityOverLifetimeModule velocityOverLifetime; // Script interface for the Particle System Velocity over Lifetime module.
			CollisionModule collision; // Script interface for the Particle System collision module.

			float time; // Playback position in seconds.
			unsigned int particleCount; // The current number of particles (Read Only).

			bool isEmitting; // Determines whether the Particle System is emitting particles. A Particle System may stop emitting when its emission module has finished, it has been paused or if the system has been stopped using Stop with the StopEmitting flag. Resume emitting by calling Play.
			bool isPaused; // Determines whether the Particle System is paused.
			bool isPlaying; // Determines whether the Particle System is playing.
			bool isStopped; // Determines whether the Particle System is stopped.

			void Pause(); // Pauses the system so no new particles are emitted and the existing particles are not updated.
			void Play(); // Starts the Particle System.
			void Stop(); // Stops playing the Particle System using the supplied stop behaviour.
			void Simulate(); // Fast-forwards the Particle System by simulating particles over the given period of time, then pauses it.

			void Clear(); // Remove all particles in the Particle System.
			void Emit(); // Emit count particles immediately.
			bool IsAlive(); // Does the Particle System contain any live particles, or will it produce more?

			vector<Particle> GetParticles(); // Gets the particles of this Particle System.
			void SetParticles(vector<Particle>); // Sets the particles of this Particle System.

			void SetMaxParticles(unsigned int max);
			bool EmitParticle(Particle particle_);

		protected:

			// lifecycle
			void Awake();
			void Update();
			void Render();
			void OnDestroy();

		private:

			vector<Particle> particles;

	};

}
