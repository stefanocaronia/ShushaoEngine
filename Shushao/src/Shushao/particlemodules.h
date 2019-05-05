#pragma once

#include "Shushao/Core.h"
#include "sepch.h"

#include "color.h"
#include "gradient.h"
#include "variation.h"

namespace se {

struct SHUSHAO_API ParticleSystemModule {
    bool enabled;  // Enable/disable the Emission module.
    void Enable() { enabled = true; }
    void Disable() { enabled = false; }
};

struct SHUSHAO_API EmissionModule : public ParticleSystemModule {
    struct SHUSHAO_API Burst {
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

    Variation rateOverDistance;  // The rate at which new particles are spawned, over distance.
    float rateOverDistanceScale = 1.0f;  // Change the rate over distance multiplier.
    Variation rateOverTime;  // The rate at which new particles are spawned, over time.
    float rateOverTimeScale = 1.0f;  // Change the rate over time multiplier.

    std::vector<Burst> bursts;

    void AddBurst(Burst burst_) {
        bursts.push_back(burst_);
    }

    void AddBurst(double time_ = 0.0, unsigned int count_ = 20, unsigned int cycles_ = 0, double interval_ = 1.0, float probability_ = 1.0f) {
        Burst b(time_, count_, cycles_, interval_, probability_);
        bursts.push_back(b);
    }
};

struct SHUSHAO_API EmitterModule : public ParticleSystemModule {
    enum class Shape {
        SPHERE
    };

    Shape shape;
    bool is2D = false;

    // CIRCLE
    float radius = 0.0f;
    int arc = 360;
};

struct SHUSHAO_API ColorOverLifetimeModule : public ParticleSystemModule {
    Gradient color;
};

struct SHUSHAO_API SizeOverLifetimeModule : public ParticleSystemModule {
    bool separateAxes = false;
    Curve size;
    glm::vec2 sizeScale = glm::vec2(1.0f);

    Curve xSize;
    Curve ySize;
};

struct SHUSHAO_API ForceOverLifetimeModule : public ParticleSystemModule {
    // TODO
};

struct SHUSHAO_API RotationBySpeedModule : public ParticleSystemModule {
    // TODO
};

struct SHUSHAO_API RotationOverLifetimeModule : public ParticleSystemModule {
    // TODO
};

struct SHUSHAO_API SizeBySpeedModule : public ParticleSystemModule {
    // TODO
};

struct SHUSHAO_API VelocityOverLifetimeModule : public ParticleSystemModule {
    // TODO
};

struct SHUSHAO_API CollisionModule : public ParticleSystemModule {
    // TODO
};

}  // namespace se
