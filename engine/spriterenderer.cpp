#include <iostream>

#include "debug.h"
#include "sprite.h"
#include "spriterenderer.h"
#include "glmanager.h"
#include "transform.h"
#include "shaders/standardshader.h"

namespace se {

	void SpriteRenderer::setup() {
		material = new Material();
		material->SetShader(new StandardShader());
	}

	SpriteRenderer::~SpriteRenderer() {
		if (material != nullptr) delete(material);
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
			Debug::Log(ERROR) << "Sprite undefined" << std::endl;
			return;
		}

		if (!sprite->ready) {
			sprite->Build();
		}

		transform->SetPivot(sprite->pivot);
		material->SetMainTexture(sprite->texture);
	}

	void SpriteRenderer::Update() {
		if (!isReady()) return;
	}

	void SpriteRenderer::Render() {

		if (!isReady()) return;

		sprite->VAO->Use();
		material->shader->Use();
		material->shader->SetRenderColor(material->color);
		material->shader->SetMVP(transform->uMVP());
		material->update();

		sprite->VAO->GetBuffer(Vbo::INDEXES)->Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
		sprite->VAO->GetBuffer(Vbo::INDEXES)->Unbind();

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
