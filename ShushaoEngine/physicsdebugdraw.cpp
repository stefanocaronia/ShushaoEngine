#include "scenemanager.h"
#include "glmanager.h"
#include "physicsdebugdraw.h"
#include "shader.h"

#include <iostream>

namespace ShushaoEngine {

	bool PhysicsDebugDraw::init() {
		if (readyToDraw) return true;
		if (!GLManager::ready) return false;

		shader = new Shader();

		shader->LoadFromString(
			#include "base.vert"
			,
			#include "base.frag"
		);

		vertices.reserve(256);
		return readyToDraw = true;
	}

	void PhysicsDebugDraw::DrawPolygon(const b2Vec2* b2vertices, int32 vertexCount, const b2Color& color) {
		if (!init()) return;

		vertices.clear();

		for (int i = 0; i < vertexCount; i++) {
			vertices.push_back({b2vertices[i].x, b2vertices[i].y, 0.0f});
		}

		initVAO();

		setColor(color.r, color.g, color.b, color.a * alpha);
		glDrawArrays(GL_LINE_LOOP, 0, vertices.size());

		closeVAO();
	}

	void PhysicsDebugDraw::DrawSolidPolygon(const b2Vec2* b2vertices, int32 vertexCount, const b2Color& color) {
		//if (!init()) return;

		vertices.clear();

		for (int i = 0; i < vertexCount; i++) {
			vertices.push_back({b2vertices[i].x, b2vertices[i].y, 0.0f});
		}

		initVAO();

		setColor(color.r, color.g, color.b, color.a * alpha);
		glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size());

		setColor(0.0f, 1.0f, 0.0f, alpha);
		glDrawArrays(GL_LINE_LOOP, 0, vertices.size());

		closeVAO();
	}

	void PhysicsDebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) {
		if (!init()) return;

		vertices.clear();
		int NUM_DIVISIONS = 31;

		for(int i = 0; i < NUM_DIVISIONS +1; i++) {
			vertices.push_back({center.x + radius * cos((float) i / NUM_DIVISIONS * M_PI * 2), center.y + radius * sin((float) i / NUM_DIVISIONS * M_PI * 2), 0.0f});
		}

		initVAO();

		glLineWidth(2);
		setColor(color.r, color.g, color.b, alpha);
		glDrawArrays(GL_LINE_LOOP, 0, vertices.size());
		glLineWidth(1);

		closeVAO();
	}

	void PhysicsDebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) {
		if (!init()) return;

		vertices.clear();
		int NUM_DIVISIONS = 31;

		for(int i = 0; i < NUM_DIVISIONS +1; i++) {
			if (i % 3 == 0) vertices.push_back({center.x,  center.y, 0.0f});
			vertices.push_back({center.x + radius * cos((float) i / NUM_DIVISIONS * M_PI * 2), center.y + radius * sin((float) i / NUM_DIVISIONS * M_PI * 2), 0.0f});
		}

		initVAO();

		glLineWidth(2);
		setColor(color.r, color.g, color.b, alpha);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, vertices.size());
		glLineWidth(1);

		closeVAO();
	}

	void PhysicsDebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {

		if (!init()) return;

		vertices.clear();
		vertices = {
			{p1.x, p1.y, 0.0f},
			{p2.x, p2.y, 0.0f},
		};

		initVAO();

		setColor(color.r, color.g, color.b, color.a * alpha);
		glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size());

		setColor(color.r, color.g, color.b, alpha);
		glDrawArrays(GL_LINE, 0, vertices.size());

		closeVAO();
	}

	void PhysicsDebugDraw::DrawTransform(const b2Transform& xf) {
		if (!init()) return;

		vertices.clear();
		vertices = {
            {0.2f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f},
            {0.0f, 0.2f, 0.0f}
		};

		glm::quat rotation = glm::quat({0.0f, 0.0f, xf.q.GetAngle()});

		for (glm::vec3& v : vertices) {
			v = (rotation * v) + glm::vec3({xf.p.x, xf.p.y, 0.0f});
		}

		initVAO();

		setColor(1, 0, 0, alpha);
		glLineWidth(2);
		setColor(1, 0, 0, alpha);
		glDrawArrays(GL_LINE_STRIP, 0, 2);
		setColor(0, 1, 0, alpha);
		glDrawArrays(GL_LINE_STRIP, 1, 2);
		glLineWidth(1);

		closeVAO();
	}

	//void PhysicsDebugDraw::initVAO(GLuint& VAO, GLuint& vertexBuffer, std::vector<glm::vec3>& vertices) {
	void PhysicsDebugDraw::initVAO() {

		glUseProgram(shader->GetProgram());

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
		glVertexAttribPointer(ShaderLocation::POSITION, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(ShaderLocation::POSITION);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glm::mat4 MVP = SceneManager::activeScene->activeCamera->Projection * SceneManager::activeScene->activeCamera->getViewMatrix() * glm::mat4();

		glUniformMatrix4fv(glGetUniformLocation(shader->GetProgram(), "MVP"), 1, GL_FALSE, &MVP[0][0]);

		glEnablei(GL_BLEND, vertexBuffer);
	}

	void PhysicsDebugDraw::closeVAO() {
		glDisablei(GL_BLEND, vertexBuffer);
		glUseProgram(0);
		glBindVertexArray(0);
	}

	void PhysicsDebugDraw::setColor(float r, float g, float b, float a) {
		glUniform4f(glGetUniformLocation(shader->GetProgram(), "renderer_color"), r, g, b, a);
	}
}
