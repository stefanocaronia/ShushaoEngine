#pragma once

#include <vector>
#include "gllibs.h"
#include "color.h"
#include "shader.h"

/// Bitmask enabled VBO
#define VBO_ALL		1
#define VBO_VERTEX	2
#define VBO_COLOR	4
#define VBO_INDEX	8
#define VBO_UV		16
#define VBO_FONT	32

/*
//initialising to multiple values with OR (|)
flags = LOG_ERRORS | LOG_WARNINGS | LOG_INCOMING;
// sets to 1 + 2 + 8 i.e. bits 0, 1 and 3

// setting one flag on, leaving the rest untouched
// OR bitmask with the current value
flags |= LOG_INCOMING;

// testing for a flag
// AND with the bitmask before testing with ==
if ((flags & LOG_WARNINGS) == LOG_WARNINGS)
   ...

// testing for multiple flags
// as above, OR the bitmasks
if ((flags & (LOG_INCOMING | LOG_OUTGOING))
         == (LOG_INCOMING | LOG_OUTGOING))
   ...

// removing a flag, leaving the rest untouched
// AND with the inverse (NOT) of the bitmask
flags &= ~LOG_OUTGOING;

// toggling a flag, leaving the rest untouched
flags ^= LOG_LOOPBACK;

*/

namespace se {


	class Vao {
		public:
			Vao(unsigned char vbos_ = VBO_VERTEX);
			~Vao();

			GLuint Id;

			unsigned char vbos = VBO_VERTEX;
			void VboEnable(unsigned char en_) {
				vbos |= en_;
			}
			void VboDisable(unsigned char en_) {
				vbos &= ~en_;
			}

			bool VboIsEnabled(unsigned char en_) {
				return ((vbos & en_) == en_);
			}

			GLuint vertexBuffer;
			GLuint vertexFontBuffer; /// NB: non si può usare assieme a vertexBuffer
			GLuint colorBuffer;
			GLuint indexBuffer;
			GLuint uvBuffer;

			bool inUse = false;

			void SetVertices(std::vector<glm::vec3>&, GLenum usage_ = GL_STATIC_DRAW);
			void SetUv(std::vector<GLclampd>&, GLenum usage_ = GL_STATIC_DRAW);
			void SetIndexes(std::vector<GLushort>&, GLenum usage_ = GL_STATIC_DRAW);
			void SetColors(std::vector<glm::vec4>&, GLenum usage_ = GL_STATIC_DRAW);
			void SetFontVertices(vector<glm::vec4>& vertices_, GLenum usage__ = GL_STATIC_DRAW);

			void Reset();
			void Init();

			void Use() {
				glBindVertexArray(Id);
				inUse = true;
			}

			void Leave() {
				glBindVertexArray(0);
				inUse = false;
			}
	};

}
