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

			bool Init(Shader*);

			bool Ready = false;

			GLenum USAGE;

			void SetVertices(std::vector<glm::vec3>);
			void SetUv(std::vector<glm::vec2>);
			void SetIndexes(std::vector<GLint>);
			void SetColors(std::vector<Color>);

		protected:

		private:

			std::vector<glm::vec3> vertices;
			std::vector<glm::vec2> uv;
			std::vector<GLint> indexes;
            std::vector<Color> colors;

			GLuint vertexBuffer;
			GLuint colorBuffer;
			GLuint indexBuffer;
			GLuint uvBuffer;
	};

}
