#pragma once

#include <vector>
#include "gllibs.h"
#include "color.h"
#include "shader.h"

namespace se {

	class Vao {
		public:
			Vao();
			~Vao();

			GLuint Id;

			GLuint vertexBuffer;
			GLuint vertexFontBuffer;
			GLuint colorBuffer;
			GLuint indexBuffer;
			GLuint uvBuffer;

			bool inUse = false;

			void SetVertices(std::vector<glm::vec3>&, GLenum usage_ = GL_STATIC_DRAW);
			void SetUv(std::vector<GLclampd>&, GLenum usage_ = GL_STATIC_DRAW);
			void SetIndexes(std::vector<GLushort>&, GLenum usage_ = GL_STATIC_DRAW);
			void SetColors(std::vector<glm::vec4>&, GLenum usage_ = GL_STATIC_DRAW);
			void SetFontVertices(std::vector<glm::vec4>&, GLenum usage_ = GL_STATIC_DRAW);

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
