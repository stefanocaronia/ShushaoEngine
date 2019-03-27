#include <vector>
#include <glm/glm.hpp>

#include "particlesystem.h"
#include "../shaders/particlesshader.h"
#include "../transform.h"

namespace se {

	using namespace std;
	using namespace glm;

    void ParticleSystem::setup() {
		material = new Material();
		material->SetShader(new ParticlesShader());

        VAO = new Vao();
		VAO->AddBuffer(Vbo::VERTICES, VBO_CONFIG_VERTEX);
		VAO->Init();

		if (playOnAwake) {
			startState = PlayableState::PLAY;
		}
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

        vector<vec3> points = {
            {0,0,0},
            {4,4,0}
        };

        VAO->Use();
        VAO->Load<vec3>(Vbo::VERTICES, points);
        VAO->Leave();

		if (startState == PlayableState::PLAY) {
			Play();
		}
	}

	void ParticleSystem::Play() {
		if (!isReady()) return;
		state = PlayableState::PLAY;
	}

	void ParticleSystem::Pause() {
		if (!isReady()) return;
		state = PlayableState::PAUSE;
	}

	void ParticleSystem::Stop() {
		if (!isReady()) return;
		state = PlayableState::STOP;
	}

	void ParticleSystem::Update() {
		if (!isReady()) return;

	}

	bool ParticleSystem::EmitParticle(Particle particle_) {
		if (particles.size() < maxParticles) {
			particles.push_back(particle_);
			return true;
		} else {
			auto it = std::find_if(particles.begin(), particles.end(), [](const Particle* p){
				return p->age >= p->lifetime;
			});
			if (it != particles.end()) {
				it->copy(particle_);
				return true;
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
		material->shader->SetM(transform->uM());
		material->update();

		VAO->GetBuffer(Vbo::VERTICES)->Bind();
		glDrawArrays(GL_POINTS, 0, VAO->GetBuffer(Vbo::VERTICES)->size);
		VAO->GetBuffer(Vbo::VERTICES)->Unbind();

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

}
