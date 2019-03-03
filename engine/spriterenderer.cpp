#include <iostream>

#include "debug.h"
#include "sprite.h"
#include "spriterenderer.h"
#include "transform.h"
#include "spritesdefaultmaterial.h"

namespace se {

	SpriteRenderer::SpriteRenderer() {
		name = "Sprite Renderer";
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

		transform->SetPivot(sprite->pivot);

		material = new SpritesDefaultMaterial();
		material->init();
		material->SetMainTexture(sprite->texture);
		// material->SetVector("texture_offset", {2.0f, 2.0f, 0, 0});
	}

	void SpriteRenderer::Update() {
		if (!isReady()) return;
	}

	void SpriteRenderer::Render() {

		if (!isReady()) return;

		material->shader->Use();
		material->shader->SetRenderColor(color);
		material->shader->SetMVP(transform->uMVP());
		sprite->VAO->Use();
		material->update();

		glActiveTexture(material->shader->GetTexture("main_texture"));
		glBindTexture(GL_TEXTURE_2D, material->mainTexture->TextureID);
		// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
		glBindTexture(GL_TEXTURE_2D, 0);

		sprite->VAO->Leave();
		material->shader->Leave();
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
