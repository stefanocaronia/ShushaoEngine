#include "spriterenderer.h"
#include "transform.h"

namespace ShushaoEngine {

	SpriteRenderer::SpriteRenderer() {
		cout << "[" << InstanceID << "] Sprite Renderer Constructor" << endl;
		name = "Sprite Renderer";

		shader = new Shader();
	}

	void SpriteRenderer::init() {

		cout << "[" << InstanceID << "] Sprite Renderer Init" << endl;

		sprite->initVAO();

		glBindVertexArray(sprite->VAO);

		glUseProgram(shader->getProgram());

		glBindBuffer(GL_ARRAY_BUFFER, sprite->vertexBuffer);
		glVertexAttribPointer(ShaderLocation::POSITION, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(ShaderLocation::POSITION);

		glBindBuffer(GL_ARRAY_BUFFER, sprite->uvBuffer);
		glVertexAttribPointer(ShaderLocation::TEXCOORD, 2, GL_FLOAT,GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(ShaderLocation::TEXCOORD);

		glUniform3f(glGetUniformLocation(shader->getProgram(), "renderColor"), color.r, color.g, color.b);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, sprite->texture->TextureID);
		glUniform1i(glGetUniformLocation(shader->getProgram(), "textureSamplerID"), GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);

		glBindVertexArray(0);
	}

	void SpriteRenderer::renderCycle() {

		glBindVertexArray(sprite->VAO);
		glUseProgram(shader->getProgram());

		glBindTexture(GL_TEXTURE_2D, sprite->texture->TextureID);
		glUniformMatrix4fv(glGetUniformLocation(shader->getProgram(), "MVP"), 1, GL_FALSE, &transform->MVP[0][0]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
	}

	void SpriteRenderer::exit() {

		cout << "[" << InstanceID << "] Sprite Renderer Exit" << endl;

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glBindVertexArray(0);
	}


}
