#include <iostream>

#include "debug.h"
#include "sprite.h"
#include "spriterenderer.h"
#include "shader.h"
#include "transform.h"

namespace se {

	SpriteRenderer::SpriteRenderer() {
		name = "Sprite Renderer";
	}

	SpriteRenderer::~SpriteRenderer() {
		if (shader != nullptr) delete(shader);
	}


	SpriteRenderer::SpriteRenderer(string n) {
		name = n;
	}

	bool SpriteRenderer::isReady() {
		return (sprite != nullptr && sprite->VAO->Ready && shader != nullptr && transform != nullptr);
	}

	void SpriteRenderer::Awake() {

		transform->SetPivot(sprite->pivot);

		shader = new Shader();
		shader->awake();

		if (!sprite->VAO->Ready) {
			sprite->VAO->Init(shader);
		}
	}

	void SpriteRenderer::Update() {

		if (!isReady()) return;

	}

	void SpriteRenderer::Render() {

		if (!isReady()) return;

		glBindVertexArray(sprite->VAO->Id);
		glUseProgram(shader->GetProgram());

		shader->color = color;
		shader->texture = GL_TEXTURE0;
		shader->mvp = &transform->MVP[0][0];
		shader->render();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, sprite->texture->TextureID);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

		glUseProgram(0);
		glBindVertexArray(0);
	}

	void SpriteRenderer::OnDestroy() {

		if (!isReady()) return;

		glUseProgram(0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);
		shader->exit();
		delete(shader);
		shader = nullptr;
	}


}
