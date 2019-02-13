#pragma once

#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>

#include "renderer.h"
#include "color.h"
#include "design.h"

namespace se {

	class Shader;

	class LineRenderer : public Renderer {

		public:

			LineRenderer();
			~LineRenderer();
			LineRenderer(std::string);

			Color color = {1.0f, 1.0f, 1.0f, 1.0f}; //	Rendering color for the Sprite graphic.

            std::vector<glm::vec3> vertices;
            std::vector<Color> colors;

			GLuint vertexBuffer;
			GLuint colorBuffer;
			GLuint VAO;

			Shader* shader;

			void AddLine(glm::vec3, glm::vec3, Color);
			void AddPolyline(std::vector<glm::vec3>, Color);
            void AddCircle(glm::vec3, float, Color, DrawMode);

			void Awake();
			void Render();
			void OnDestroy();

	};

}
