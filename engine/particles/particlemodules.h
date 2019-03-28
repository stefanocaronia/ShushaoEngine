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

    struct Burst {
        double time;
        unsigned int count;
        unsigned int cycles;
        double interval;
        float probability;

        unsigned int cycle = 0;
        double cycleTime = 0.0;

        Burst(double time_ = 0.0, unsigned int count_ = 20, unsigned int cycles_ = 0, double interval_ = 1.0, float probability_ = 1.0f) {
            Set(time_, count_, cycles_, interval_, probability_);
        }

        void Set(double time_ = 0.0, unsigned int count_ = 20, unsigned int cycles_ = 0, double interval_ = 1.0, float probability_ = 1.0f) {
            time = time_;
            count = count_;
            cycles = cycles_;
            interval = interval_;
            probability = probability_;
        }

        void reset() {
            cycle = 0;
            cycleTime = 0.0;
        }
    };

    unsigned int burstCount;  //	The current number of bursts.

    //float rateOverDistance;            // The rate at which new particles are spawned, over distance.
    //float rateOverDistanceMultiplier;  // Change the rate over distance multiplier.
    float rateOverTime;                // The rate at which new particles are spawned, over time.
    //float rateOverTimeMultiplier;      // Change the rate over time multiplier.

    // void GetBurst(); // Get a single burst from the array of bursts.
    // void GetBursts(); // Get the burst array.
    // void SetBurst(); // Set a single burst in the array of bursts.
    // void SetBursts(); // Set the burst array.

    std::vector<Burst> bursts;

    void AddBurst(Burst burst_) {
        bursts.push_back(burst_);
    }

    void AddBurst(double time_ = 0.0, unsigned int count_ = 20, unsigned int cycles_ = 0, double interval_ = 1.0, float probability_ = 1.0f) {
        Burst b(time_, count_, cycles_, interval_, probability_);
        bursts.push_back(b);
    }
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
