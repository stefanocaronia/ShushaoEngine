#include <iostream>

#include "debug.h"
#include "sprite.h"
#include "spriterenderer.h"
#include "glmanager.h"
#include "transform.h"
#include "standardshader.h"

namespace se {

	SpriteRenderer::SpriteRenderer() {
		name = "Sprite Renderer";
		material = new Material();
		material->SetShader(GLManager::GetShader<StandardShader>());
	}

	SpriteRenderer::~SpriteRenderer() {
		if (material != nullptr) delete(material);
	}

	SpriteRenderer::SpriteRenderer(string n) {
		name = n;
	}

	bool SpriteRenderer::isReady() {
		return (
			sprite != nullptr &&
			material != nullptr &&
			material->shader != nullptr &&
			transform != nullptr
		);
	}

	void SpriteRenderer::Awake() {

		if (sprite == nullptr) {
			Debug::Log(ERROR) << "Sprite undefined" << endl;
			return;
		}

		if (!sprite->ready) {
			sprite->Build();
		}

		transform->SetPivot(sprite->pivot);


		material->SetMainTexture(sprite->texture);
		// material->SetVector("texture_offset", {2.0f, 2.0f, 0, 0});
	}

	void SpriteRenderer::Update() {
		if (!isReady()) return;
	}

	void SpriteRenderer::Render() {

		if (!isReady()) return;

		sprite->VAO->Use();
		material->shader->Use();
		material->shader->SetRenderColor(color);
		material->shader->SetMVP(transform->uMVP());
		material->update();

		glActiveTexture(material->shader->GetTexture("diffuse_map"));
		glBindTexture(GL_TEXTURE_2D, material->mainTexture->TextureID);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
		glBindTexture(GL_TEXTURE_2D, 0);

		material->shader->Leave();
		sprite->VAO->Leave();
	}

	void SpriteRenderer::OnDestroy() {

		if (!isReady()) return;

		sprite->VAO->Leave();
		material->shader->Leave();
		material->shader->exit();
		delete(material);
		material = nullptr;
	}
}
