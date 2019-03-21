#pragma once

#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>

#include "renderer.h"
#include "color.h"
#include "design.h"
#include "vao.h"
#include "globals.h"

namespace se {

	class Shader;

	class GeometryRenderer : public Renderer {

		public:

			virtual void setup();

			~GeometryRenderer();

			Vao* VAO;
			Shader* shader;

			RenderMode renderMode = RenderMode::WORLD;

            std::vector<glm::vec3> vertices;
            std::vector<glm::vec4> colors;

			void AddLine(glm::vec3, glm::vec3, Color);
			void AddPolyline(std::vector<glm::vec3>, Color);
            void AddCircle(glm::vec3, float, Color, DrawMode);

			void Awake();
			void Update();
			void Render();
			void OnDestroy();

	};

}
