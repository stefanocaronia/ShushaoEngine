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

			void SetVertices(std::vector<glm::vec3>&);
			void SetUv(GLclampd*);
			void SetIndexes(GLushort*);
			void SetColors(std::vector<Color>&);

		protected:

		private:

			std::vector<glm::vec3> vertices;
            std::vector<Color> colors;
			GLclampd uv[8] = {99};
			GLushort indexes[6] = {99};

			GLuint vertexBuffer;
			GLuint colorBuffer;
			GLuint indexBuffer;
			GLuint uvBuffer;
	};

}
