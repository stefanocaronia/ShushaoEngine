#include <iostream>

#include "spriterenderer.h"
#include "transform.h"
#include "debug.h"

using namespace std;

namespace ShushaoEngine {

	SpriteRenderer::SpriteRenderer() {
		cout << "[" << InstanceID << "] Sprite Renderer Constructor" << endl;
		name = "Sprite Renderer";

		//color = {1.0f, 1.0f, 1.0f, 1.0f};

	}

	SpriteRenderer::SpriteRenderer(string n) {
		cout << "[" << InstanceID << "] Sprite Renderer Constructor" << endl;
		name = n;

		//color = {1.0f, 1.0f, 1.0f, 1.0f};
	}

	void SpriteRenderer::init() {

		LOG("In init spriterenderer: Shader " + shader->name);
		LOG("In init spriterenderer: Sprite " + sprite->name);

		sprite->initVAO();

		glBindVertexArray(sprite->VAO);

		glBindBuffer(GL_ARRAY_BUFFER, sprite->vertexBuffer);
		glVertexAttribPointer(ShaderLocation::POSITION, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(ShaderLocation::POSITION);

		glBindBuffer(GL_ARRAY_BUFFER, sprite->uvBuffer);
		glVertexAttribPointer(ShaderLocation::TEXCOORD, 2, GL_FLOAT,GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(ShaderLocation::TEXCOORD);

		glActiveTexture(0);
		glBindTexture(GL_TEXTURE_2D, sprite->texture->TextureID);
		glUniform1i(glGetUniformLocation(shader->getProgram(), "textureSamplerID"), 0);
		glBindTexture(GL_TEXTURE_2D, 0);

		glBindVertexArray(0);
	}

	void SpriteRenderer::render() {

		glBindVertexArray(sprite->VAO);
		glUseProgram(shader->getProgram());

		glActiveTexture(0);
		glBindTexture(GL_TEXTURE_2D, sprite->texture->TextureID);
		glUniform4f(glGetUniformLocation(shader->getProgram(), "renderColor"), color.r, color.g, color.b, color.a);
		glUniformMatrix4fv(glGetUniformLocation(shader->getProgram(), "MVP"), 1, GL_FALSE, &transform->MVP[0][0]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindTexture(GL_TEXTURE_2D, 0);

		glUseProgram(0);
		glBindVertexArray(0);

	}

	void SpriteRenderer::exit() {

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glBindVertexArray(0);
	}


}
