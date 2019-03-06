#include <glm/glm.hpp>

#include "debug.h"
#include "vbo.h"
#include "shader.h"

namespace se {

	using namespace glm;
	using namespace std;

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

	VboConfiguration VBO_CONFIG_NORMAL = {
		GL_ARRAY_BUFFER,
		ShaderLocation::LOCATION_NORMAL,
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
		if (ready) {
			return this;
		}

		glGenBuffers(1, &Id);

		if (config.location > 0) {
			Bind();
			glEnableVertexAttribArray(config.location);
			glVertexAttribPointer(config.location, config.blocksize, config.type, config.normalized, config.stride, config.pointer);
			// Unbind();
		}

		ready = true;

		return this;
	}

	Vbo* Vbo::Delete() {
		glDeleteBuffers(1, &Id);
		return this;
	}

	Vbo* Vbo::Bind() {
		//if (!config.target) return this;
		glBindBuffer(config.target, Id);
		return this;
	}

	Vbo* Vbo::Unbind() {
		//if (!config.target) return this;
		glBindBuffer(config.target, 0);
		return this;
	}
}
