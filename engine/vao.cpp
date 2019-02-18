#include "vao.h"
#include "debug.h"
#include <glm/glm.hpp>

namespace se {

	Vao::Vao(GLenum usage_) {
		USAGE = usage_;
	}

	Vao::~Vao() {
		glDeleteBuffers(1, &vertexBuffer);
		glDeleteBuffers(1, &indexBuffer);
		glDeleteBuffers(1, &colorBuffer);
		glDeleteBuffers(1, &uvBuffer);
	}

	bool Vao::Init(Shader* shader) {

		if (Ready || shader == nullptr) return false;

		using namespace glm;

		glGenVertexArrays(1, &Id);
		glBindVertexArray(Id);

		if (vertices.size() > 0) {
			glGenBuffers(1, &vertexBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3), &vertices[0], USAGE);
			glVertexAttribPointer(shader->aCoord, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
			glEnableVertexAttribArray(shader->aCoord);
		}

		if (indexes[0] != 99) {
			glGenBuffers(1, &indexBuffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), &indexes, USAGE);
		}

		if (uv[0] != 99) {
			glGenBuffers(1, &uvBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
			glBufferData(GL_ARRAY_BUFFER, sizeof(uv), &uv, USAGE);
			glVertexAttribPointer(shader->aTextureCoord, 2, GL_DOUBLE, GL_FALSE, 0, (void*)0);
			glEnableVertexAttribArray(shader->aTextureCoord);
		}

		if (colors.size() > 0) {
			glGenBuffers(1, &colorBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
			glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(vec4), &colors[0], USAGE);
			glVertexAttribPointer(shader->aColor, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
			glEnableVertexAttribArray(shader->aColor);
		}

		glBindVertexArray(0);

		Ready = true;
		return true;
	}

	void Vao::SetVertices(vector<glm::vec3>& vertices_) {
		vertices = vertices_;
	}

	void Vao::SetUv(GLclampd* uv_) {
		memcpy(uv, uv_, sizeof(GLclampd) * 8);
	}

	void Vao::SetIndexes(GLushort* indexes_) {
		memcpy(indexes, indexes_, sizeof(GLushort) * 6);
	}

	void Vao::SetColors(vector<Color>& colors_) {
		colors = colors_;
	}
}
