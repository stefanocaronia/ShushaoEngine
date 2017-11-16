#include <iostream>

#include "spriterenderer.h"
#include "transform.h"
#include "utility.h"
#include "debug.h"

using namespace std;

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

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(sprite->vertices), &sprite->vertices, GL_STATIC_DRAW);

		glGenBuffers(1, &indexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(sprite->indexes), &sprite->indexes, GL_STATIC_DRAW);

		glGenBuffers(1, &uvBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(sprite->uv), &sprite->uv, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glVertexAttribPointer(ShaderLocation::POSITION, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(ShaderLocation::POSITION);

		glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
		glVertexAttribPointer(ShaderLocation::TEXCOORD, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(ShaderLocation::TEXCOORD);

		glBindVertexArray(0);

	}

	void SpriteRenderer::Update() {

		if (!isReady()) return;

		//transform->position += vec3(sprite->pivot, 0.0f);

		// TODO translation pivot point

	}

	void SpriteRenderer::Render() {

		if (!isReady()) return;

		glBindVertexArray(VAO);
		glUseProgram(shader->getProgram());

		// uniforms
		glUniform4f(glGetUniformLocation(shader->getProgram(), "renderer_color"), color.r, color.g, color.b, color.a);
		glUniform1i(glGetUniformLocation(shader->getProgram(), "base_texture"), GL_TEXTURE0);
		glUniformMatrix4fv(glGetUniformLocation(shader->getProgram(), "MVP"), 1, GL_FALSE, &transform->MVP[0][0]);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, sprite->texture->TextureID);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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
