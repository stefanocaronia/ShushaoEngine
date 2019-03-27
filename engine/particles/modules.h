#pragma once

#include <glm/glm.hpp>

#include "../color.h"

namespace se {

    enum class EmitterShape {
        CIRCLE,
        EDGE,
        BOX
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
        EmitterShape shape;

        // CIRCLE
        float radius;
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
