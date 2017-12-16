#include <iostream>

#include "sprite.h"
#include "spriterenderer.h"
#include "shader.h"
#include "transform.h"

namespace ShushaoEngine {

	SpriteRenderer::SpriteRenderer() {
		name = "Sprite Renderer";
	}

	SpriteRenderer::SpriteRenderer(string n) {
		name = n;
	}

	bool SpriteRenderer::isReady() {
		return (sprite != nullptr && shader != nullptr);
	}

	void SpriteRenderer::Awake() {

		if (!isReady()) return;

		transform->setPivot(sprite->pivot);
	}

	void SpriteRenderer::Update() {

		if (!isReady()) return;

	}

	void SpriteRenderer::Render() {

		if (!isReady()) return;

		glBindVertexArray(sprite->VAO);
		glUseProgram(shader->getProgram());

		// uniforms
		glUniform4f(glGetUniformLocation(shader->getProgram(), "renderer_color"), color.r, color.g, color.b, color.a);
		glUniform1i(glGetUniformLocation(shader->getProgram(), "base_texture"), GL_TEXTURE0);
		glUniformMatrix4fv(glGetUniformLocation(shader->getProgram(), "MVP"), 1, GL_FALSE, &transform->MVP[0][0]);

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
	}


}
