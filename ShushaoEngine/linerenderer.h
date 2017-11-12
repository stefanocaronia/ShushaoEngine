#pragma once

#include <vector>
#include <glm.hpp>

#include "libs.h"
#include "renderer.h"
#include "color.h"
#include "shader.h"

namespace ShushaoEngine {

	using namespace glm;
	using namespace std;

	class LineRenderer : public Renderer {

		public:

			LineRenderer();
			~LineRenderer();
			LineRenderer(string);

			Color color = {1.0f, 1.0f, 1.0f, 1.0f}; //	Rendering color for the Sprite graphic.

            vector<vec3> vertices;
            vector<Color> colors;

			GLuint vertexBuffer;
			GLuint colorBuffer;
			GLuint VAO;

			Shader* shader;

			void AddLine(vec3, vec3, Color);
			void AddPolyline(vector<vec3>, Color);

			void init();
			void exit();

			void render();
	};

}
