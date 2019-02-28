#include <glm/glm.hpp>

#include "vao.h"
#include "debug.h"

namespace se {

	using namespace glm;

	Vao::Vao(unsigned char vbos_) {
		vbos = vbos_;
	}

	Vao::~Vao() {
		if (VboIsEnabled(VBO_VERTEX)) glDeleteBuffers(1, &vertexBuffer);
		if (VboIsEnabled(VBO_FONT)) glDeleteBuffers(1, &vertexFontBuffer);
		if (VboIsEnabled(VBO_INDEX)) glDeleteBuffers(1, &indexBuffer);
		if (VboIsEnabled(VBO_COLOR)) glDeleteBuffers(1, &colorBuffer);
		if (VboIsEnabled(VBO_UV)) glDeleteBuffers(1, &uvBuffer);

		glDeleteVertexArrays(1, &Id);
	}

	void Vao::Init() {
		glGenVertexArrays(1, &Id);
		Use();

		if (VboIsEnabled(VBO_VERTEX)) {
			glGenBuffers(1, &vertexBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
			glEnableVertexAttribArray(ShaderLocation::LOCATION_POSITION);
			glVertexAttribPointer(ShaderLocation::LOCATION_POSITION, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		if (VboIsEnabled(VBO_INDEX)) {
			glGenBuffers(1, &indexBuffer);
		}

		if (VboIsEnabled(VBO_COLOR)) {
			glGenBuffers(1, &colorBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
			glEnableVertexAttribArray(ShaderLocation::LOCATION_COLOR);
			glVertexAttribPointer(ShaderLocation::LOCATION_COLOR, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		if (VboIsEnabled(VBO_UV)) {
			glGenBuffers(1, &uvBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
			glEnableVertexAttribArray(ShaderLocation::LOCATION_TEXCOORD);
			glVertexAttribPointer(ShaderLocation::LOCATION_TEXCOORD, 2, GL_DOUBLE, GL_FALSE, 0, (void*)0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		if (VboIsEnabled(VBO_FONT)) {
			glGenBuffers(1, &vertexFontBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, vertexFontBuffer);
			glEnableVertexAttribArray(ShaderLocation::LOCATION_POSITION);
			glVertexAttribPointer(ShaderLocation::LOCATION_POSITION, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		Leave();
	}

	void Vao::Reset() {
		if (VboIsEnabled(VBO_VERTEX)) glDeleteBuffers(1, &vertexBuffer);
		if (VboIsEnabled(VBO_FONT)) glDeleteBuffers(1, &vertexFontBuffer);
		if (VboIsEnabled(VBO_INDEX)) glDeleteBuffers(1, &indexBuffer);
		if (VboIsEnabled(VBO_COLOR)) glDeleteBuffers(1, &colorBuffer);
		if (VboIsEnabled(VBO_UV)) glDeleteBuffers(1, &uvBuffer);
		glDeleteVertexArrays(1, &Id);
		Init();
	}

	void Vao::SetVertices(vector<glm::vec3>& vertices_, GLenum usage_) {
		if (!VboIsEnabled(VBO_VERTEX)) {
			Debug::Log(ERROR) << "SetVertices: VBO is not enabled" << endl;
			return;
		}

		if (!inUse) {
			Debug::Log(ERROR) << "SetVertices: VAO is not in use" << endl;
			return;
		}

		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(vec3), &vertices_[0], usage_);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Vao::SetFontVertices(vector<glm::vec4>& vertices_, GLenum usage_) {
		if (!VboIsEnabled(VBO_FONT)) {
			Debug::Log(ERROR) << "SetFontVertices: VBO is not enabled" << endl;
			return;
		}

		if (!inUse) {
			Debug::Log(ERROR) << "SetFontVertices: VAO is not in use" << endl;
			return;
		}
		glBindBuffer(GL_ARRAY_BUFFER, vertexFontBuffer);
		glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(vec4), &vertices_[0], usage_);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Vao::SetUv(std::vector<GLclampd>& uv_, GLenum usage_) {
		if (!VboIsEnabled(VBO_UV)) {
			Debug::Log(ERROR) << "SetUv: VBO is not enabled" << endl;
			return;
		}

		if (!inUse) {
			Debug::Log(ERROR) << "SetUv: VAO is not in use" << endl;
			return;
		}
		glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
		glBufferData(GL_ARRAY_BUFFER, uv_.size() * sizeof(GLclampd), &uv_[0], usage_);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Vao::SetIndexes(std::vector<GLushort>& indexes_, GLenum usage_) {
		if (!VboIsEnabled(VBO_INDEX)) {
			Debug::Log(ERROR) << "SetIndexes: VBO is not enabled" << endl;
			return;
		}

		if (!inUse) {
			Debug::Log(ERROR) << "SetIndexes: VAO is not in use" << endl;
			return;
		}
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes_.size() * sizeof(GLushort), &indexes_[0], usage_);
	}

	void Vao::SetColors(vector<glm::vec4>& colors_, GLenum usage_) {
		if (!VboIsEnabled(VBO_COLOR)) {
			Debug::Log(ERROR) << "SetColors: VBO is not enabled" << endl;
			return;
		}

		if (!inUse) {
			Debug::Log(ERROR) << "SetColors: VAO is not in use" << endl;
			return;
		}
		glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
		glBufferData(GL_ARRAY_BUFFER, colors_.size() * sizeof(vec4), &colors_[0], usage_);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}


}
