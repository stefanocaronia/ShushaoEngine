#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <vector>

#include "color.h"
#include "shader.h"
#include "vao.h"
#include "rect.h"

namespace se {

	enum class DrawElement {
		POINT,
		LINE,
		POLYGON,
		CIRCLE,
		VECTOR,
		RAY
	};

	enum class DrawMode {
		HOLLOW,
		FULL
	};

	struct DrawCall {
		DrawElement element = DrawElement::LINE;
		DrawMode mode = DrawMode::HOLLOW;
		std::vector<glm::vec3> vertices;
		glm::vec3 position = {0.0f, 0.0f, 0.0f};
		glm::vec3 start = {0.0f, 0.0f, 0.0f};
		glm::vec3 dir = {0.0f, 0.0f, 0.0f};
		glm::vec3 end = {0.0f, 0.0f, 0.0f};
		int tickness = 1;
		float radius = 1.0f;
		Color color = {1.0f, 1.0f, 1.0f, 1.0f};
		float duration = 0.0f; // seconds
		float expire = 0.0f;
		bool normalized = false;

		bool operator==(DrawCall other) {
			return (color == other.color &&
					radius == other.radius &&
					end == other.end &&
					start == other.start &&
					dir == other.dir &&
					position == other.position &&
					vertices == other.vertices &&
					normalized == other.normalized &&
					mode == other.mode &&
					element == other.element);
		}
	};

	class Design {

		public:

			static void DrawPoint(glm::vec3 position, Color color, float duration = 0.0f);
			static void DrawPoint(glm::vec3 position, Color color, int tickness, float duration = 0.0f);
			static void DrawLine(glm::vec3 start, glm::vec3 end, Color color, float duration = 0.0f);
			static void DrawRay(glm::vec3 start, glm::vec3 dir, Color color, float duration = 0.0f);
			static void DrawPolygon(std::vector<glm::vec3> vertices_, Color color, DrawMode mode = DrawMode::HOLLOW, float duration = 0.0f);
			static void DrawCircle(glm::vec3 position, float radius, Color color, DrawMode mode = DrawMode::HOLLOW, float duration = 0.0f);
			static void DrawRect(glm::vec3 position, Rect rect, Color color, DrawMode mode = DrawMode::HOLLOW, float duration = 0.0f);
			static void DrawVector(glm::vec3 start, glm::vec3 end, Color color, bool normalized = false, float duration = 0.0f);

			static void ProcessDrawCalls();

			static void Clear();

		private:

			static Shader* shader;
			static bool ready;
			static Vao* VAO;
			static std::vector<glm::vec3> vertices;

			static bool Init();

			static void AddDrawCall(DrawCall);

			static void _drawPoint(glm::vec3 position, Color color, int tickness = 1);
			static void _drawLine(glm::vec3 start, glm::vec3 end, Color color);
			static void _drawRay(glm::vec3 start, glm::vec3 dir, Color color);
			static void _drawPolygon(std::vector<glm::vec3> vertices_, Color color, DrawMode mode = DrawMode::HOLLOW);
			static void _drawCircle(glm::vec3 position, float radius, Color color, DrawMode mode = DrawMode::HOLLOW);
			static void _drawVector(glm::vec3 start, glm::vec3 end, Color color, bool normalized = false);

			static std::vector<DrawCall> drawCalls;
	};
}
