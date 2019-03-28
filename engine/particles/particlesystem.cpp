#include <math.h>
#include <glm/glm.hpp>
#include <vector>

#include "../shaders/particlesshader.h"
#include "../transform.h"
#include "../utility.h"
#include "particlesystem.h"

namespace se {

using namespace std;
using namespace glm;

void ParticleSystem::setup() {
    material = new Material();
    material->SetShader(new ParticlesShader());

    VAO = new Vao();
    VAO->AddBuffer("positions", {GL_ARRAY_BUFFER, ShaderLocation::LOCATION_POSITION, 3, GL_FLOAT, GL_FALSE, 0, (void*)0, GL_DYNAMIC_DRAW});
    VAO->AddBuffer("colors", {GL_ARRAY_BUFFER, ShaderLocation::LOCATION_COLOR, 4, GL_FLOAT, GL_FALSE, 0, (void*)0, GL_DYNAMIC_DRAW});
    VAO->AddBuffer("sizes", {GL_ARRAY_BUFFER, ShaderLocation::LOCATION_SIZE, 2, GL_FLOAT, GL_FALSE, 0, (void*)0, GL_DYNAMIC_DRAW});
    VAO->Init();
}

ParticleSystem::~ParticleSystem() {
    if (material != nullptr) delete (material);
    delete (VAO);
    VAO = nullptr;
}

void ParticleSystem::SetTexture(Texture* value_) {
    texture = value_;
}

void ParticleSystem::SetMaxParticles(unsigned int max) {
    maxParticles = max;
    particles.clear();
    particles.reserve(max);
    positions.reserve(max);
    colors.reserve(max);
    sizes.reserve(max);
}

bool ParticleSystem::isReady() {
    return (
        material != nullptr &&
        material->shader != nullptr &&
        transform != nullptr);
}

void ParticleSystem::Awake() {
    if (texture != nullptr) {
        material->SetMainTexture(texture);
    }

    if (startState == Playable::State::PLAY) {
        Play();
    }
}

void ParticleSystem::Play() {
    if (!isReady()) return;
    state = Playable::State::PLAY;
    startTime = Time::GetTime();
    isLoopEnded = false;
    elapsed = 0.0f;
    isPlaying = true;
    isStopped = false;
    isPaused = false;
}

void ParticleSystem::Pause() {
    if (!isReady()) return;
    state = Playable::State::PAUSE;
    isPlaying = false;
    isStopped = false;
    isPaused = true;
}

void ParticleSystem::Stop() {
    if (!isReady()) return;
    state = Playable::State::STOP;
    Clear();
    isPlaying = false;
    isStopped = true;
    isPaused = false;
}

void ParticleSystem::EmitParticle() {
    if (!emitter.enabled) return;

    // common properties
    Color color = startColor;
    float rotation = startRotation;
    vec2 size = startSize;
    float lifetime = startLifetime;
    vec3 position = transform->localPosition;
    vec3 direction = transform->forward;

    switch (emitter.shape) {
        case EmitterModule::Shape::SPHERE:

            float inclination = glm::radians((float)util::random(0, emitter.arc));
            float azimuth = glm::radians((float)util::random(0, emitter.arc));

            float sInclination = sinf(inclination);

            if (emitter.is2D) {
                direction.x = cosf(azimuth);
                direction.y = sinf(azimuth);
                direction.z = 0.0f;
            } else {
                direction.x = sInclination * cosf(azimuth);
                direction.y = sInclination * sinf(azimuth);
                direction.z = cosf(inclination);
            }

            AddParticle(
                (direction * emitter.radius) + position,  // position
                direction * startSpeed,                   // velocity
                color,                                    // color
                rotation,                                 // rotation
                size,                                     // size
                lifetime                                  // lifetime
            );

            break;
    }
}

void ParticleSystem::Emit(unsigned int count) {
    for (unsigned int c = 0; c < count; c++) {
        EmitParticle();
    }
}

void ParticleSystem::UpdateParticles() {
    positions.clear();
    colors.clear();
    sizes.clear();

    particleCount = 0;

    // update particles
    for (auto& particle : particles) {
        if (particle->age >= particle->lifetime) {
            continue;
        }
        particleCount++;
        particle->position += particle->velocity * Time::deltaTime;
        particle->age += Time::deltaTime;

        positions.push_back(particle->position);
        colors.push_back(particle->color.rgba());
        sizes.push_back(particle->size);
    }
}

void ParticleSystem::Update() {
    if (!isReady()) return;

    if (startDelay > 0.0f && Time::GetTime() - startTime < startDelay) {
        return;
    }

    if (isPlaying && emission.enabled && !isLoopEnded) {
        // generate particles
        toEmit += emission.rateOverTime * Time::deltaTime;
        if (toEmit >= 1.0) {
            int toEmitInt = floor(toEmit);
            Emit(toEmitInt);
            toEmit -= toEmitInt;
        }

        // TODO: rateOverDistance con i delta del movimento del transform

        ProcessBursts();

        isEmitting = true;
    } else {
        isEmitting = false;
    }

    if (isPlaying) {
        UpdateParticles();
        LoadBuffers();
    }

    if (isLoopEnded && particleCount == 0) {
        Stop();
        LoadBuffers();
    }

    elapsed += Time::deltaTime;
    if (elapsed >= duration) {
        if (!loop) {
            isLoopEnded = true;
        }
        elapsed = 0.0f;
    }
}

void ParticleSystem::ProcessBursts() {
    if (emission.bursts.size() > 0) {
        for (auto& b : emission.bursts) {
            if (b.cycle == 0) {
                if (elapsed >= b.time) {
                    if (b.probability >= 1.0f || util::happens(b.probability)) {
                        Emit(b.count);
                    }
                    b.cycle++;
                    b.cycleTime = Time::GetTime();
                }
            } else {
                if (b.cycles > 0 && b.cycle >= b.cycles) continue;
                if (Time::GetTime() - b.cycleTime >= b.interval) {
                    if (b.probability >= 1.0f || util::happens(b.probability)) {
                        Emit(b.count);
                    }
                    b.cycle++;
                    b.cycleTime = Time::GetTime();
                }
            }
        }
    }
}

void ParticleSystem::Clear() {
    positions.clear();
    colors.clear();
    sizes.clear();

    for (Particle* p : particles) {
        delete (p);
        p = nullptr;
    }
    particles.clear();
}

void ParticleSystem::LoadBuffers() {
    // load vertices
    VAO->Use();

    if (last_positions != positions) {
        VAO->Load<vec3>("positions", positions);
        last_positions.swap(positions);
    }

    if (last_colors != colors) {
        VAO->Load<vec4>("colors", colors);
        last_colors.swap(colors);
    }

    if (last_sizes != sizes) {
        VAO->Load<vec2>("sizes", sizes);
        last_sizes.swap(sizes);
    }

    VAO->Leave();
}

bool ParticleSystem::AddParticle(Particle* particle_) {
    if (particles.size() < maxParticles) {
        particles.push_back(particle_);
        return true;
    } else {
        for (Particle* p : particles) {
            if (p->age >= p->lifetime) {
                // delete(p);
                p = particle_;
                return true;
                break;
            }
        }
    }
    return false;
}

bool ParticleSystem::AddParticle(glm::vec3 position_, glm::vec3 velocity_, Color color_, float rotation_, glm::vec2 size_, float lifetime_) {
    if (particles.size() < maxParticles) {
        Particle* particle = new Particle(position_, velocity_, color_, rotation_, size_, lifetime_);
        particles.push_back(particle);
        return true;
    } else {
        for (Particle* p : particles) {
            if (p->age >= p->lifetime) {
                p->reset(position_, velocity_, color_, rotation_, size_, lifetime_);
                return true;
                break;
            }
        }
    }
    return false;
}

void ParticleSystem::Render() {
    if (!isReady() || isStopped) return;

    VAO->Use();
    material->shader->Use();
    material->shader->SetRenderColor(material->color);
    material->shader->SetMVP(transform->uMVP());
    material->shader->SetP(transform->uP());
    material->update();

    VAO->GetBuffer("positions")->Bind();
    glEnablei(GL_BLEND, VAO->GetBuffer("positions")->Id);
    glDrawArrays(GL_POINTS, 0, VAO->GetBuffer("positions")->size);
    glDisablei(GL_BLEND, VAO->GetBuffer("positions")->Id);
    VAO->GetBuffer("positions")->Unbind();

    material->shader->Leave();
    VAO->Leave();
}

void ParticleSystem::OnDestroy() {
    if (!isReady()) return;
    VAO->Leave();
    material->shader->Leave();
    material->shader->exit();
    delete (material);
    material = nullptr;
}

void ParticleSystem::SetPlayOnAwake(bool value_) {
    playOnAwake = value_;
    if (playOnAwake) {
        startState = Playable::State::PLAY;
    }
}

void ParticleSystem::SetStartDelay(float value_) {
    startDelay = value_;
}

void ParticleSystem::SetStartLifetime(float value_) {
    startLifetime = value_;
}

void ParticleSystem::SetStartSpeed(float value_) {
    startSpeed = value_;
}

void ParticleSystem::SetStartSize(glm::vec2 value_) {
    startSize = value_;
}

void ParticleSystem::SetStartColor(Color value_) {
    startColor = value_;
}

void ParticleSystem::SetStartRotation(float value_) {
    startRotation = value_;
}

}  // namespace se
