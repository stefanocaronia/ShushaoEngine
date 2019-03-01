#include <glm/glm.hpp>

#include "vao.h"
#include "debug.h"

namespace se {

	using namespace glm;
	using namespace std;

	//{ #region VBO

	Vbo::~Vbo() {
		Delete();
	}

	Vbo* Vbo::Init(GLenum target_) {
		glGenBuffers(1, &Id);
		target = target_;
		return this;
	}

	Vbo* Vbo::Delete() {
		glDeleteBuffers(1, &Id);
		return this;
	}

	Vbo* Vbo::Bind() {
		if (!target) target = GL_ARRAY_BUFFER;
		glBindBuffer(target, Id);
		return this;
	}

	Vbo* Vbo::Unbind() {
		if (!target) return this;
		glBindBuffer(target, 0);
		return this;
	}

	//}

	//{ #region VAO

	Vao::Vao(unsigned char vbos_) {
		vbos = vbos_;
	}

	Vao::~Vao() {
		if (VBO_VERTEX_ENABLED) { delete(vertexBuffer); vertexBuffer = nullptr; }
		if (VBO_FONT_ENABLED) { delete(vertexFontBuffer); vertexFontBuffer = nullptr; }
		if (VBO_INDEX_ENABLED) { delete(indexBuffer); indexBuffer = nullptr; }
		if (VBO_COLOR_ENABLED) { delete(colorBuffer); colorBuffer = nullptr; }
		if (VBO_UV_ENABLED) { delete(uvBuffer); uvBuffer = nullptr; }

		glDeleteVertexArrays(1, &Id);
	}

	Vao* Vao::VboEnable(unsigned char vboflag) {
		vbos |= vboflag;
		return this;
	}

	Vao* Vao::VboDisable(unsigned char vboflag) {
		vbos &= ~vboflag;
		return this;
	}

	bool Vao::VboIsEnabled(unsigned char vboflag) {
		return ((vbos & vboflag) == vboflag);
	}


	Vao* Vao::Use() {
		glBindVertexArray(Id);
		inUse = true;
		return this;
	}

	Vao* Vao::Leave() {
		glBindVertexArray(0);
		inUse = false;
		return this;
	}

	Vao* Vao::Init() {
		glGenVertexArrays(1, &Id);
		Use();

		if (VBO_FONT_ENABLED) {
			VboDisable(VBO_VERTEX);
		}

		if (VBO_VERTEX_ENABLED) {
			vertexBuffer = new Vbo();
			vertexBuffer->Init(GL_ARRAY_BUFFER)->Bind();
			glEnableVertexAttribArray(ShaderLocation::LOCATION_POSITION);
			glVertexAttribPointer(ShaderLocation::LOCATION_POSITION, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
			vertexBuffer->Unbind();
		}

		if (VBO_INDEX_ENABLED) {
			indexBuffer = new Vbo();
			indexBuffer->Init(GL_ELEMENT_ARRAY_BUFFER);
		}

		if (VBO_COLOR_ENABLED) {
			colorBuffer = new Vbo();
			colorBuffer->Init(GL_ARRAY_BUFFER)->Bind();
			glEnableVertexAttribArray(ShaderLocation::LOCATION_COLOR);
			glVertexAttribPointer(ShaderLocation::LOCATION_COLOR, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
			colorBuffer->Unbind();
		}

		if (VBO_UV_ENABLED) {
			uvBuffer = new Vbo();
			uvBuffer->Init(GL_ARRAY_BUFFER)->Bind();
			glEnableVertexAttribArray(ShaderLocation::LOCATION_TEXCOORD);
			glVertexAttribPointer(ShaderLocation::LOCATION_TEXCOORD, 2, GL_DOUBLE, GL_FALSE, 0, (void*)0);
			uvBuffer->Unbind();
		}

		if (VBO_FONT_ENABLED) {
			vertexFontBuffer = new Vbo();
			vertexFontBuffer->Init(GL_ARRAY_BUFFER)->Bind();
			glEnableVertexAttribArray(ShaderLocation::LOCATION_FONTCOORD);
			glVertexAttribPointer(ShaderLocation::LOCATION_FONTCOORD, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
			vertexFontBuffer->Unbind();
		}

		Leave();
		return this;
	}

	Vao* Vao::SetVertices(vector<glm::vec3>& elements_, GLenum usage_) {

		if (!VBO_VERTEX_ENABLED || vertexBuffer == nullptr) {
			Debug::Log(ERROR) << "SetVertices: VBO is not enabled" << endl;
			return this;
		}

		if (!inUse) {
			Debug::Log(ERROR) << "SetVertices: VAO is not in use" << endl;
			return this;
		}

		vertexBuffer->Bind()->Load<vec3>(elements_, usage_);
		vertexBuffer->Unbind();

		return this;
	}

	Vao* Vao::SetFontVertices(vector<glm::vec4>& elements_, GLenum usage_) {

		if (!VBO_FONT_ENABLED || vertexFontBuffer == nullptr) {
			Debug::Log(ERROR) << "SetFontVertices: VBO is not enabled" << endl;
			return this;
		}

		if (!inUse) {
			Debug::Log(ERROR) << "SetFontVertices: VAO is not in use" << endl;
			return this;
		}

		vertexFontBuffer->Bind()->Load<vec4>(elements_, usage_);
		vertexFontBuffer->Unbind();

		return this;
	}

	Vao* Vao::SetUv(std::vector<GLclampd>& elements_, GLenum usage_) {

		if (!VBO_UV_ENABLED || uvBuffer == nullptr) {
			Debug::Log(ERROR) << "SetUv: VBO is not enabled" << endl;
			return this;
		}

		if (!inUse) {
			Debug::Log(ERROR) << "SetUv: VAO is not in use" << endl;
			return this;
		}

		uvBuffer->Bind()->Load<GLclampd>(elements_, usage_);
		uvBuffer->Unbind();

		return this;
	}

	Vao* Vao::SetIndexes(std::vector<GLushort>& elements_, GLenum usage_) {

		if (!VBO_INDEX_ENABLED || indexBuffer == nullptr) {
			Debug::Log(ERROR) << "SetIndexes: VBO is not enabled" << endl;
			return this;
		}

		if (!inUse) {
			Debug::Log(ERROR) << "SetIndexes: VAO is not in use" << endl;
			return this;
		}

		indexBuffer->Bind()->Load<GLushort>(elements_, usage_);
		//indexBuffer->Unbind();

		return this;
	}

	Vao* Vao::SetColors(vector<glm::vec4>& elements_, GLenum usage_) {

		if (!VBO_COLOR_ENABLED || colorBuffer == nullptr) {
			Debug::Log(ERROR) << "SetColors: VBO is not enabled" << endl;
			return this;
		}

		if (!inUse) {
			Debug::Log(ERROR) << "SetColors: VAO is not in use" << endl;
			return this;
		}

		colorBuffer->Bind()->Load<vec4>(elements_, usage_);
		colorBuffer->Unbind();

		return this;
	}

	//}

}
