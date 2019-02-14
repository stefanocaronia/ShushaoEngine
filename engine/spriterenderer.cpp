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
		return (sprite != nullptr && sprite->VAO > 0 && shader != nullptr && transform != nullptr);
	}

	void SpriteRenderer::Awake() {

		transform->SetPivot(sprite->pivot);

		shader = new Shader();

		glUseProgram(shader->GetProgram());

		uniform_renderer_color = glGetUniformLocation(shader->GetProgram(), "renderer_color");
		uniform_base_texture = glGetUniformLocation(shader->GetProgram(), "base_texture");
		uniform_mvp = glGetUniformLocation(shader->GetProgram(), "MVP");

		glUseProgram(0);
	}

	void SpriteRenderer::Update() {

		if (!isReady()) return;

	}

	void SpriteRenderer::Render() {

		if (!isReady()) return;

		glBindVertexArray(sprite->VAO);
		glUseProgram(shader->GetProgram());

		// uniforms
		glUniform4f(uniform_renderer_color, color.r, color.g, color.b, color.a);
		glUniform1i(uniform_base_texture, GL_TEXTURE0);
		glUniformMatrix4fv(uniform_mvp, 1, GL_FALSE, &transform->MVP[0][0]);

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
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glBindVertexArray(0);
		delete(shader);
		shader = nullptr;
	}


}
