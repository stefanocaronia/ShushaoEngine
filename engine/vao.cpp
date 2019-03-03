#include <glm/glm.hpp>

#include "vao.h"
#include "debug.h"

namespace se {

	using namespace glm;
	using namespace std;

	//{ #region VBO

	VboConfiguration VBO_CONFIG_VERTEX = {
		GL_ARRAY_BUFFER,
		ShaderLocation::LOCATION_POSITION,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0,
		GL_STATIC_DRAW
	};

	VboConfiguration VBO_CONFIG_INDEX = {
		GL_ELEMENT_ARRAY_BUFFER,
		0
	};

	VboConfiguration VBO_CONFIG_COLOR {
		GL_ARRAY_BUFFER,
		ShaderLocation::LOCATION_COLOR,
		4,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0,
		GL_STATIC_DRAW
	};

	VboConfiguration VBO_CONFIG_UV {
		GL_ARRAY_BUFFER,
		ShaderLocation::LOCATION_TEXCOORD,
		2,
		GL_DOUBLE,
		GL_FALSE,
		0,
		(void*)0,
		GL_STATIC_DRAW
	};

	VboConfiguration VBO_CONFIG_FONT {
		GL_ARRAY_BUFFER,
		ShaderLocation::LOCATION_FONTCOORD,
		4,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0,
		GL_DYNAMIC_DRAW
	};

	Vbo::~Vbo() {
		Delete();
	}

	Vbo* Vbo::Init() {
		glGenBuffers(1, &Id);

		if (config.location > 0) {
			Bind();
			glEnableVertexAttribArray(config.location);
			glVertexAttribPointer(config.location, config.blocksize, config.type, config.normalized, config.stride, config.pointer);
			Unbind();
		}

		return this;
	}

	Vbo* Vbo::Delete() {
		glDeleteBuffers(1, &Id);
		return this;
	}

	Vbo* Vbo::Bind() {
		if (!config.target) return this;
		glBindBuffer(config.target, Id);
		return this;
	}

	Vbo* Vbo::Unbind() {
		if (!config.target) return this;
		glBindBuffer(config.target, 0);
		return this;
	}

	//}

	//{ #region VAO

	Vao::~Vao() {
		// if (VBO_VERTEX_ENABLED) { delete(vertexBuffer); vertexBuffer = nullptr; }
		// if (VBO_FONT_ENABLED) { delete(vertexFontBuffer); vertexFontBuffer = nullptr; }
		// if (VBO_INDEX_ENABLED) { delete(indexBuffer); indexBuffer = nullptr; }
		// if (VBO_COLOR_ENABLED) { delete(colorBuffer); colorBuffer = nullptr; }
		// if (VBO_UV_ENABLED) { delete(uvBuffer); uvBuffer = nullptr; }

		for (auto& it : buffers) {
			if (it.second != nullptr) {
				Debug::Log << "Cancello buffer" << it.second->name  << endl; //<< " (" + util::classtitle(typeid(*it.second).name()) +")"
				delete(it.second);
				it.second = nullptr;
			}
		}

		buffers.clear();

		glDeleteVertexArrays(1, &Id);
	}

	Vbo* Vao::AddBuffer(string name_, VboConfiguration config_) {
		buffers[name_] = new Vbo(config_);
		buffers[name_]->name = name_;
		return buffers[name_];
	}

	Vbo* Vao::AddBuffer(Vbo* vbo) {
		buffers[vbo->name] = vbo;
		return vbo;
	}

	Vbo* Vao::GetBuffer(std::string name) {
		auto it = buffers.find(name);
		if (it == buffers.end()) return nullptr;
		return (Vbo*)buffers[name];
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

		for (auto& it : buffers) {
			if (it.second != nullptr) {
				(Vbo*)it.second->Init();
			}
		}

		Leave();
		return this;
	}

	//}
}
