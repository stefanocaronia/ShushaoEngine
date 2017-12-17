#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <vector>

#include "color.h"
#include "shader.h"

namespace ShushaoEngine {

	class Design {

		public:

			static void DrawLine(glm::vec3 start, glm::vec3 end, Color color);

		private:

			static Shader* shader;
			static bool readyToDraw;
			static GLuint VAO;
			static GLuint vertexBuffer;
			static std::vector<glm::vec3> vertices;

			static bool initDraw();
			static void initVAO();
			static void setColor(Color);
			static void closeVAO();
	};
}
