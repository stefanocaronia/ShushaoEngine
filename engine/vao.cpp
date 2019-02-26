#include "vao.h"
#include "debug.h"
#include <glm/glm.hpp>

namespace se {

	using namespace glm;

	Vao::Vao(GLenum usage_) {
		GL_USAGE = usage_;
		glGenVertexArrays(1, &Id);
	}

	Vao::~Vao() {
		glDeleteBuffers(1, &vertexBuffer);
		glDeleteBuffers(1, &indexBuffer);
		glDeleteBuffers(1, &colorBuffer);
		glDeleteBuffers(1, &uvBuffer);

		glDeleteVertexArrays(1, &Id);
	}

	void Vao::Reset() {
		glDeleteBuffers(1, &vertexBuffer);
		glDeleteBuffers(1, &indexBuffer);
		glDeleteBuffers(1, &colorBuffer);
		glDeleteBuffers(1, &uvBuffer);
		glDeleteVertexArrays(1, &Id);
		glGenVertexArrays(1, &Id);
	}

	void Vao::SetVertices(vector<glm::vec3>& vertices_) {
		Bind();
		glDeleteBuffers(1, &vertexBuffer);
		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(vec3), &vertices_[0], GL_USAGE);
		glVertexAttribPointer(ShaderLocation::LOCATION_POSITION, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(ShaderLocation::LOCATION_POSITION);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		Unbind();
	}

	void Vao::SetUv(std::vector<GLclampd>& uv_) {
		Bind();
		glDeleteBuffers(1, &uvBuffer);
		glGenBuffers(1, &uvBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
		glBufferData(GL_ARRAY_BUFFER, uv_.size() * sizeof(GLclampd), &uv_[0], GL_USAGE);
		glVertexAttribPointer(ShaderLocation::LOCATION_TEXCOORD, 2, GL_DOUBLE, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(ShaderLocation::LOCATION_TEXCOORD);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		Unbind();
	}

	void Vao::SetIndexes(std::vector<GLushort>& indexes_) {
		Bind();
		glDeleteBuffers(1, &indexBuffer);
		glGenBuffers(1, &indexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes_.size() * sizeof(GLushort), &indexes_[0], GL_USAGE);
		Unbind();
	}

	void Vao::SetColors(vector<glm::vec4>& colors_) {
		Bind();
		glDeleteBuffers(1, &colorBuffer);
		glGenBuffers(1, &colorBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
		glBufferData(GL_ARRAY_BUFFER, colors_.size() * sizeof(vec4), &colors_[0], GL_USAGE);
		glVertexAttribPointer(ShaderLocation::LOCATION_COLOR, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(ShaderLocation::LOCATION_COLOR);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		Unbind();
	}

}
