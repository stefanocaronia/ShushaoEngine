#pragma once

#include <vector>
#include "gllibs.h"
#include "color.h"
#include "shader.h"

namespace se {

	class Vao {
		public:
			Vao(GLenum usage_ = GL_STATIC_DRAW);
			~Vao();

			GLuint Id;
			GLenum GL_USAGE;

			GLuint vertexBuffer;
			GLuint colorBuffer;
			GLuint indexBuffer;
			GLuint uvBuffer;

			void SetVertices(std::vector<glm::vec3>&);
			void SetUv(std::vector<GLclampd>&);
			void SetIndexes(std::vector<GLushort>&);
			void SetColors(std::vector<glm::vec4>&);

			void Reset();

			void Bind() {
				glBindVertexArray(Id);
			}
			void Unbind() {
				glBindVertexArray(0);
			}
	};

}
