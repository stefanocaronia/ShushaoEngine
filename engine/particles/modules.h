#pragma once

#include <glm/glm.hpp>

#include "../color.h"

namespace se {

    struct MainModule {

        float duration; // The duration of the Particle System in seconds.
        bool loop; // Is the Particle System looping?
        float startDelay; // Start delay in seconds.
        float startLifetime; // The total lifetime in seconds that each new particle will have.
        float startSpeed; // The initial speed of particles when emitted.
        float startSize; // The initial size of particles when emitted.
        bool startSize3D; // A flag to enable specifying particle size individually for each axis.
        float startSizeMultiplier; // A multiplier of the initial size of particles when emitted.
        float startSizeX; // The initial size of particles along the X axis when emitted.
        float startSizeXMultiplier; // The initial size multiplier of particles along the X axis when emitted.
        float startSizeY; // The initial size of particles along the Y axis when emitted.
        float startSizeYMultiplier; // The initial size multiplier of particles along the Y axis when emitted.
        float startSizeZ; // The initial size of particles along the Z axis when emitted.
        float startSizeZMultiplier; // The initial size multiplier of particles along the Z axis when emitted.

        float startRotation; // The initial rotation of particles when emitted.
        // glm::vec3 startRotation3D; // A flag to enable 3D particle rotation.
        Color startColor; // The initial color of particles when emitted.

        unsigned int maxParticles; // The maximum number of particles to emit.
        bool playOnAwake; // If set to true, the Particle System will automatically start playing on startup.
        float simulationSpeed; // Override the default playback speed of the Particle System.

        //void* stopAction;	Select whether to Disable or Destroy the GameObject, or to call the OnParticleSystemStopped script Callback, when the Particle System is stopped and all particles have died.
        bool useUnscaledTime; // When true, use the unscaled delta time to simulate the Particle System. Otherwise, use the scaled delta time.
    };

    struct EmissionModule {
        unsigned int burstCount; //	The current number of bursts.
        bool enabled; // Enable/disable the Emission module.
        float rateOverDistance; // The rate at which new particles are spawned, over distance.
        float rateOverDistanceMultiplier; // Change the rate over distance multiplier.
        float rateOverTime; // The rate at which new particles are spawned, over time.
        float rateOverTimeMultiplier; // Change the rate over time multiplier.

        // void GetBurst(); // Get a single burst from the array of bursts.
        // void GetBursts(); // Get the burst array.
        // void SetBurst(); // Set a single burst in the array of bursts.
        // void SetBursts(); // Set the burst array.
    };

    struct ShapeModule {

    };

    struct ColorOverLifetimeModule {};
    struct ForceOverLifetimeModule {};
    struct RotationBySpeedModule {};
    struct RotationOverLifetimeModule {};
    struct SizeBySpeedModule {};
    struct SizeOverLifetimeModule {};
    struct VelocityOverLifetimeModule {};
    struct CollisionModule {};

}
