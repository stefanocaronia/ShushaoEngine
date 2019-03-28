#pragma once

#include <glm/glm.hpp>

#include "../color.h"

namespace se {

using namespace glm;

struct ParticleSystemModule {
    bool enabled;  // Enable/disable the Emission module.
    void Enable() { enabled = true; }
    void Disable() { enabled = false; }
};

struct EmissionModule : public ParticleSystemModule {
    unsigned int burstCount;  //	The current number of bursts.

    float rateOverDistance;            // The rate at which new particles are spawned, over distance.
    float rateOverDistanceMultiplier;  // Change the rate over distance multiplier.
    float rateOverTime;                // The rate at which new particles are spawned, over time.
    float rateOverTimeMultiplier;      // Change the rate over time multiplier.

    // void GetBurst(); // Get a single burst from the array of bursts.
    // void GetBursts(); // Get the burst array.
    // void SetBurst(); // Set a single burst in the array of bursts.
    // void SetBursts(); // Set the burst array.
};

struct EmitterModule : public ParticleSystemModule {
    enum class Shape {
        SPHERE
    };

    Shape shape;
    bool is2D = false;

    // CIRCLE
    float radius = 0.0f;
    int arc = 360;
};

struct ColorOverLifetimeModule : public ParticleSystemModule {

};
struct ForceOverLifetimeModule : public ParticleSystemModule {

};
struct RotationBySpeedModule : public ParticleSystemModule {

};
struct RotationOverLifetimeModule : public ParticleSystemModule {

};
struct SizeBySpeedModule : public ParticleSystemModule {

};
struct SizeOverLifetimeModule : public ParticleSystemModule {

};
struct VelocityOverLifetimeModule : public ParticleSystemModule {

};
struct CollisionModule : public ParticleSystemModule {

};

}  // namespace se
