#pragma once

#include "../core.h"

#include "../shaders/shader.h"
#include "../vao.h"

    namespace se {

    class SHUSHAO_API PhysicsDebugDraw : public b2Draw {
    public:
        bool Init();
        //std::vector<glm::vec3> vertices;
        float alpha = 0.4f;
        Vao* VAO;
        Shader* shader = nullptr;
        bool ready = false;

        void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
        void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
        void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);
        void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);
        void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);
        void DrawTransform(const b2Transform& xf);
    };

}  // namespace se
