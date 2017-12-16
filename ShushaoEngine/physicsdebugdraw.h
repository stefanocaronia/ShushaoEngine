#pragma once

#include <Box2D/Box2D.h>
#include <gllibs.h>

namespace ShushaoEngine {

	class Shader;

	class PhysicsDebugDraw : public b2Draw {
		public:

			void init();
			void initVAO();
			void setColor(float r, float g, float b, float a);
			void closeVAO();

			GLuint VAO;
			GLuint vertexBuffer;
			std::vector<glm::vec3> vertices;
			float alpha = 0.4f;

			Shader* shader = nullptr;

			void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
			void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
			void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);
			void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);
			void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);
			void DrawTransform(const b2Transform& xf);
	};


}
