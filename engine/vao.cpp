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
			glVertexAttribPointer(shader->aPosition, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
			glEnableVertexAttribArray(shader->aPosition);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		if (indexes.size() > 0) {
			glGenBuffers(1, &indexBuffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(GLint), &indexes[0], USAGE);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		if (uv.size() > 0) {
			glGenBuffers(1, &uvBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
			glBufferData(GL_ARRAY_BUFFER, uv.size() * sizeof(vec2), &uv[0], USAGE);
			glVertexAttribPointer(shader->aTextureCoord, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
			glEnableVertexAttribArray(shader->aTextureCoord);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		if (colors.size() > 0) {
			glGenBuffers(1, &colorBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
			glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(vec4), &colors[0], USAGE);
			glVertexAttribPointer(shader->aColor, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
			glEnableVertexAttribArray(shader->aColor);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		glBindVertexArray(0);

		Ready = true;
		return true;
	}

	void Vao::SetVertices(vector<glm::vec3> vertices_) {
		vertices = vertices_;
	}

	void Vao::SetUv(vector<glm::vec2> uv_) {
		uv = uv_;
	}

	void Vao::SetIndexes(vector<GLint> indexes_) {
		indexes = indexes_;
	}

	void Vao::SetColors(vector<Color> colors_) {
		colors = colors_;
	}
}
