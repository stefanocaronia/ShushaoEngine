#pragma once

#include <vector>

#include "../component.h"
#include "modules.h"
#include "particle.h"

namespace se {

	class ParticleSystem : public Component {

		public:

			MainModule main; // Access the main Particle System settings.
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

		protected:

			// lifecycle
			void Awake();
			void Update();
			void Render();

		private:

			vector<Particle> particles;

	};

}
