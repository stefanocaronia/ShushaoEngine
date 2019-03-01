#pragma once

#include <vector>
#include "gllibs.h"
#include "color.h"
#include "shader.h"

/// Bitmask enabled VBO
#define VBO_VERTEX	1
#define VBO_COLOR	2
#define VBO_INDEX	4
#define VBO_UV		8
#define VBO_FONT	16
#define VBO_ALL		VBO_VERTEX | VBO_COLOR | VBO_INDEX | VBO_UV

#define VBO_VERTEX_ENABLED 	VboIsEnabled(VBO_VERTEX)
#define VBO_COLOR_ENABLED 	VboIsEnabled(VBO_COLOR)
#define VBO_INDEX_ENABLED 	VboIsEnabled(VBO_INDEX)
#define VBO_UV_ENABLED 		VboIsEnabled(VBO_UV)
#define VBO_FONT_ENABLED 	VboIsEnabled(VBO_FONT)
#define VBO_ALL_ENABLED 	VboIsEnabled(VBO_ALL)

#define USE_BUFFER_SUBDATA 	1

/* 	Bitmask usage vademecum

	flags = LOG_ERRORS | LOG_WARNINGS | LOG_INCOMING; // initialising to multiple values with OR (|)
	flags |= LOG_INCOMING; // setting one flag on, leaving the rest untouched
	if ((flags & LOG_WARNINGS) == LOG_WARNINGS) // testing for a flag
	if ((flags & (LOG_INCOMING | LOG_OUTGOING)) == (LOG_INCOMING | LOG_OUTGOING)) // testing for multiple flags
	flags &= ~LOG_OUTGOING; // removing a flag, leaving the rest untouched
	flags ^= LOG_LOOPBACK; // toggling a flag, leaving the rest untouched
*/

namespace se {

	class Vbo {
		public:

			~Vbo();

			GLuint Id = 0; // Vbo ID GL
			GLsizeiptr buffersize = 0;
			GLenum target = GL_ARRAY_BUFFER;

			Vbo* Init(GLenum target_);
			Vbo* Delete();
			Vbo* Bind();
			Vbo* Unbind();

			template<class T>
			Vbo* Load(std::vector<T>& elements_, GLenum usage_ = GL_STATIC_DRAW) {
				GLsizeiptr oldsize = buffersize;
				buffersize = elements_.size() * sizeof(T);
				if (oldsize == buffersize) {
					glBufferSubData(target, 0, buffersize, &elements_[0]);
				} else {
					glBufferData(target, buffersize, &elements_[0], usage_);
				}
				return this;
			}
	};

	class Vao {
		public:

			Vao(unsigned char vbos_ = VBO_VERTEX);
			~Vao();

			GLuint Id; // Vao ID GL
			bool inUse = false;
			unsigned char vbos = VBO_VERTEX;

			Vbo* vertexBuffer = nullptr;
			Vbo* vertexFontBuffer = nullptr;
			Vbo* colorBuffer = nullptr;
			Vbo* indexBuffer = nullptr;
			Vbo* uvBuffer = nullptr;

			Vao* Init();
			Vao* Use();
			Vao* Leave();

			Vao* VboEnable(unsigned char vboflag);
			Vao* VboDisable(unsigned char vboflag);
			bool VboIsEnabled(unsigned char vboflag);

			Vao* SetVertices(std::vector<glm::vec3>&, GLenum usage_ = GL_STATIC_DRAW);
			Vao* SetUv(std::vector<GLclampd>&, GLenum usage_ = GL_STATIC_DRAW);
			Vao* SetIndexes(std::vector<GLushort>&, GLenum usage_ = GL_STATIC_DRAW);
			Vao* SetColors(std::vector<glm::vec4>&, GLenum usage_ = GL_STATIC_DRAW);
			Vao* SetFontVertices(vector<glm::vec4>& vertices_, GLenum usage__ = GL_DYNAMIC_DRAW);

	};

}
