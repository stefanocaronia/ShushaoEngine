#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "../color.h"
#include "../material.h"
#include "../playable.h"
#include "../renderer.h"
#include "../texture.h"
#include "../vao.h"
#include "particlemodules.h"

namespace se {

struct Particle {
    glm::vec3 position;
    glm::vec3 velocity;
    Color color;
    float rotation;
    glm::vec2 size;
    float lifetime;
    float age;

    Particle(glm::vec3 position_, glm::vec3 velocity_, Color color_, float rotation_, glm::vec2 size_, float lifetime_) {
		reset(position_, velocity_, color_, rotation_, size_, lifetime_);
	}

    void reset(glm::vec3 position_, glm::vec3 velocity_, Color color_, float rotation_, glm::vec2 size_, float lifetime_) {
        position = position_;
        velocity = velocity_;
        color = color_;
        rotation = rotation_;
        size = size_;
        lifetime = lifetime_;
        age = 0.0f;
    }

    void copy(Particle other) {
        position = other.position;
        velocity = other.velocity;
        color = other.color;
        rotation = other.rotation;
        size = other.size;
        lifetime = other.lifetime;
        age = other.age;
    }
};

class ParticleSystem : public Renderer, public Playable {
public:
    virtual void setup();
    ~ParticleSystem();
    bool isReady();

    //void* stopAction;										// Select whether to Disable or Destroy the GameObject, or to call the OnParticleSystemStopped script Callback, when the Particle System is stopped and all particles have died.
    //bool useUnscaledTime; 								// When true, use the unscaled delta time to simulate the Particle System. Otherwise, use the scaled delta time.
    EmissionModule emission;                          // emission module.
    EmitterModule emitter;                            // Shape module.
    ColorOverLifetimeModule colorOverLifetime;        // color over lifetime module.
    ForceOverLifetimeModule forceOverLifetime;        // force over lifetime module.
    RotationBySpeedModule rotationBySpeed;            // Rotation by Speed module.
    RotationOverLifetimeModule rotationOverLifetime;  // Rotation over Lifetime module.
    SizeBySpeedModule sizeBySpeed;                    // Size by Speed module.
    SizeOverLifetimeModule sizeOverLifetime;          // Size over Lifetime module.
    VelocityOverLifetimeModule velocityOverLifetime;  // Velocity over Lifetime module.
    CollisionModule collision;                        // collision module.

    float time;  // Playback position in seconds.

    void Pause();  // Pauses the system so no new particles are emitted and the existing particles are not updated.
    void Play();   // Starts the Particle System.
    void Stop();   // Stops playing the Particle System using the supplied stop behaviour.
    // void Simulate(); // Fast-forwards the Particle System by simulating particles over the given period of time, then pauses it.

    void Emit(unsigned int count);  // Emit count particles immediately.
    void Clear();

    vector<Particle> GetParticles();      // Gets the particles of this Particle System.
    void SetParticles(vector<Particle>);  // Sets the particles of this Particle System.
    void SetTexture(Texture* value_);
    void SetMaxParticles(unsigned int max);
    bool AddParticle(Particle* particle_);
    bool AddParticle(glm::vec3 position_, glm::vec3 velocity_, Color color_, float rotation_, glm::vec2 size_, float lifetime_);
    void SetPlayOnAwake(bool value_);
    void SetStartDelay(float value_);
    void SetStartLifetime(float value_);
    void SetStartSpeed(float value_);
    void SetStartSize(glm::vec2 value_);
    void SetStartColor(Color value_);
    void SetStartRotation(float value_);

    bool IsAlive();

protected:
    // lifecycle
    void Awake();
    void Update();
    void Render();
    void OnDestroy();

private:
    Texture* texture = nullptr;
    Material* material = nullptr;
    Vao* VAO = nullptr;

    bool isEmitting;  // Determines whether the Particle System is emitting particles. A Particle System may stop emitting when its emission module has finished, it has been paused or if the system has been stopped using Stop with the StopEmitting flag. Resume emitting by calling Play.
    bool isPaused;    // Determines whether the Particle System is paused.
    bool isPlaying;   // Determines whether the Particle System is playing.
    bool isStopped;   // Determines whether the Particle System is stopped.

    unsigned int particleCount;

    void EmitParticle();
    void UpdateParticles();
    void ProcessBursts();
    void LoadBuffers();

    vector<Particle*> particles;

    unsigned int maxParticles;  // The maximum number of particles to emit.
    bool playOnAwake;           // If set to true, the Particle System will automatically start playing on startup.
    // float simulationSpeed = 1.0f; // Override the default playback speed of the Particle System.

    float startDelay;     // Start delay in seconds.
    float startLifetime;  // The total lifetime in seconds that each new particle will have.
    float startSpeed;     // The initial speed of particles when emitted.
    glm::vec2 startSize;  // The initial size of particles when emitted.
    float startRotation;  // The initial rotation of particles when emitted.
    Color startColor;     // The initial color of particles when emitted.

    double timeInterval = 0.0;
    double startTime = 0.0;
    double toEmit = 0.0;

    bool isLoopEnded = false;

    std::vector<glm::vec3> positions;
    std::vector<glm::vec4> colors;
    std::vector<glm::vec2> sizes;

    std::vector<glm::vec3> last_positions;
    std::vector<glm::vec4> last_colors;
    std::vector<glm::vec2> last_sizes;
};

}  // namespace se
