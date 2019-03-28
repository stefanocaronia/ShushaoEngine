#include <vector>
#include <glm/glm.hpp>

#include "particlesystem.h"
#include "../shaders/particlesshader.h"
#include "../transform.h"
#include "../utility.h"

namespace se {

	using namespace std;
	using namespace glm;

    void ParticleSystem::setup() {
		material = new Material();
		material->SetShader(new ParticlesShader());

        VAO = new Vao();
		VAO->AddBuffer("positions", {
			GL_ARRAY_BUFFER,
			ShaderLocation::LOCATION_POSITION,
			3, GL_FLOAT, GL_FALSE, 0, (void*)0,
			GL_DYNAMIC_DRAW
		});
		VAO->AddBuffer("colors", {
			GL_ARRAY_BUFFER,
			ShaderLocation::LOCATION_COLOR,
			4, GL_FLOAT, GL_FALSE, 0, (void*)0,
			GL_DYNAMIC_DRAW
		});
		VAO->AddBuffer("sizes", {
			GL_ARRAY_BUFFER,
			ShaderLocation::LOCATION_SIZE,
			2, GL_FLOAT, GL_FALSE, 0, (void*)0,
			GL_DYNAMIC_DRAW
		});
		VAO->Init();
	}

    ParticleSystem::~ParticleSystem() {
		if (material != nullptr) delete(material);
		delete(VAO);
		VAO = nullptr;
	}

	void ParticleSystem::SetMaxParticles(unsigned int max) {
		maxParticles = max;
		particles.clear();
		particles.reserve(max);
	}

    bool ParticleSystem::isReady() {
		return (
			material != nullptr &&
			material->shader != nullptr &&
			transform != nullptr
		);
	}

	void ParticleSystem::Awake() {
		if (texture != nullptr) {
			material->SetMainTexture(texture);
		}

		if (startState == PlayableState::PLAY) {
            state = PlayableState::PLAY;
			Play();
		}
	}

	void ParticleSystem::Play() {
		if (!isReady()) return;
		state = PlayableState::PLAY;
        startTime = Time::GetTime();
        end = false;
	}

	void ParticleSystem::Pause() {
		if (!isReady()) return;
		state = PlayableState::PAUSE;
	}

	void ParticleSystem::Stop() {
		if (!isReady()) return;
		state = PlayableState::STOP;
        stopTime = Time::GetTime();
	}

    void ParticleSystem::EmitParticle() {
        Particle* particle = new Particle();
        switch (shape.shape) {
            case EmitterShape::POINT:

                float inclination = glm::radians((float)util::randomInRange(0, 360));
                float azimuth = glm::radians((float)util::randomInRange(0, 360));

                float sInclination = sinf(inclination);

                float X = sInclination * cosf( azimuth );
                float Y = sInclination * sinf( azimuth );
                float Z = cosf(inclination);

                /* float X = cosf(azimuth);
                float Y = sinf(azimuth);
                float Z = 0.0f; */

                vec3 direction(X, Y, Z);

                particle->position = transform->localPosition;
                particle->velocity = direction * startSpeed;
                particle->color = startColor;
                particle->rotation = 0.0f;
                particle->lifetime = startLifetime;
                particle->size = startSize;
                AddParticle(particle);
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

        // update particles
        for(auto& particle : particles) {
            if (particle->age >= particle->lifetime) continue;
            particle->position += particle->velocity * Time::deltaTime;
            particle->age += Time::deltaTime;
            positions.push_back(particle->position);
            colors.push_back(particle->color.rgba());
            sizes.push_back(particle->size);
        }
    }

	void ParticleSystem::Update() {
		if (!isReady()) return;

		if (state == PlayableState::PLAY && !(startDelay > 0 && Time::GetTime() - startTime < startDelay)) {

			// generate particles
			//if (Time::GetTime() - emissionTime > 1.0 / emission.rateOverTime) {
                EmitParticle();
		        emissionTime = Time::GetTime();
			//}
        }

        if (!end) {
            UpdateParticles();
            LoadBuffers();
        }

        if (state == PlayableState::STOP && Time::GetTime() - stopTime > startLifetime) {
            if (!end) {
                Clear();
                LoadBuffers();
                end = true;
            }
        }

        elapsed += Time::deltaTime;
        if (elapsed >= duration && !loop) {
            Stop();
        }
	}

    void ParticleSystem::Clear() {
        positions.clear();
        colors.clear();
        sizes.clear();

        for (auto& p : particles) {
            delete(p);
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

	void ParticleSystem::Render() {

		if (!isReady()) return;

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
		delete(material);
		material = nullptr;
	}


    void ParticleSystem::SetPlayOnAwake(bool value_) {
        playOnAwake = value_;
        if (playOnAwake) {
            startState = PlayableState::PLAY;
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

}
