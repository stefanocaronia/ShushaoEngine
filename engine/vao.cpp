#include <glm/glm.hpp>

#include "vao.h"
#include "debug.h"

namespace se {

	using namespace glm;

	Vao::Vao() {}

	Vao::~Vao() {
		glDeleteBuffers(1, &vertexBuffer);
		glDeleteBuffers(1, &vertexFontBuffer);
		glDeleteBuffers(1, &indexBuffer);
		glDeleteBuffers(1, &colorBuffer);
		glDeleteBuffers(1, &uvBuffer);

		glDeleteVertexArrays(1, &Id);
	}

	void Vao::Init() {
		glGenVertexArrays(1, &Id);
		Use();

		glGenBuffers(1, &vertexBuffer);
		glGenBuffers(1, &vertexFontBuffer);
		glGenBuffers(1, &indexBuffer);
		glGenBuffers(1, &colorBuffer);
		glGenBuffers(1, &uvBuffer);

		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glEnableVertexAttribArray(ShaderLocation::LOCATION_POSITION);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ARRAY_BUFFER, vertexFontBuffer);
		glEnableVertexAttribArray(ShaderLocation::LOCATION_POSITION);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
		glEnableVertexAttribArray(ShaderLocation::LOCATION_TEXCOORD);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
		glEnableVertexAttribArray(ShaderLocation::LOCATION_COLOR);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		Leave();
	}

	void Vao::Reset() {
		glDeleteBuffers(1, &vertexBuffer);
		glDeleteBuffers(1, &vertexFontBuffer);
		glDeleteBuffers(1, &indexBuffer);
		glDeleteBuffers(1, &colorBuffer);
		glDeleteBuffers(1, &uvBuffer);
		glDeleteVertexArrays(1, &Id);

		Init();
	}

	void Vao::SetVertices(vector<glm::vec3>& vertices_, GLenum usage_) {
		if (!inUse) {
			Debug::Log(ERROR) << "SetVertices: VAO is not in use" << endl;
			return;
		}
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(vec3), &vertices_[0], usage_);
		glVertexAttribPointer(ShaderLocation::LOCATION_POSITION, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Vao::SetFontVertices(vector<glm::vec4>& vertices_, GLenum usage_) {
		if (!inUse) {
			Debug::Log(ERROR) << "SetFontVertices: VAO is not in use" << endl;
			return;
		}
		glBindBuffer(GL_ARRAY_BUFFER, vertexFontBuffer);
		glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(vec4), &vertices_[0], usage_);
		glVertexAttribPointer(ShaderLocation::LOCATION_POSITION, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Vao::SetUv(std::vector<GLclampd>& uv_, GLenum usage_) {
		if (!inUse) {
			Debug::Log(ERROR) << "SetUv: VAO is not in use" << endl;
			return;
		}
		glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
		glBufferData(GL_ARRAY_BUFFER, uv_.size() * sizeof(GLclampd), &uv_[0], usage_);
		glVertexAttribPointer(ShaderLocation::LOCATION_TEXCOORD, 2, GL_DOUBLE, GL_FALSE, 0, (void*)0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Vao::SetIndexes(std::vector<GLushort>& indexes_, GLenum usage_) {
		if (!inUse) {
			Debug::Log(ERROR) << "SetIndexes: VAO is not in use" << endl;
			return;
		}
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes_.size() * sizeof(GLushort), &indexes_[0], usage_);
	}

	void Vao::SetColors(vector<glm::vec4>& colors_, GLenum usage_) {
		if (!inUse) {
			Debug::Log(ERROR) << "SetColors: VAO is not in use" << endl;
			return;
		}
		glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
		glBufferData(GL_ARRAY_BUFFER, colors_.size() * sizeof(vec4), &colors_[0], usage_);
		glVertexAttribPointer(ShaderLocation::LOCATION_COLOR, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}


}
