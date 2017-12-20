#include "debug.h"
#include "design.h"
#include "glmanager.h"
#include "scenemanager.h"

namespace ShushaoEngine {

	bool Design::initDraw() {
		if (readyToDraw) return true;
		if (!GLManager::ready) return false;

		shader = new Shader();
		shader->LoadFromString(
			#include "base.vert"
			,
			#include "base.frag"
		);
		shader->name = "Base";

		vertices.reserve(256);
		return readyToDraw = true;
	}

	void Design::Clear() {
		drawCalls.clear();
		if (shader != nullptr) delete(shader);
	}

	void Design::AddDrawCall(DrawCall call) {
		auto it = std::find(drawCalls.begin(), drawCalls.end(), call);
		if (it == drawCalls.end()) {
			 drawCalls.push_back(call);
		}
	}

	void Design::ProcessDrawCalls() {
		drawCalls.erase(std::remove_if(drawCalls.begin(), drawCalls.end(), [=](DrawCall& c) {
			return (c.duration > 0.0f && c.expire > 0.0f && Time::time > c.expire);
		}), drawCalls.end());

		for (auto it = drawCalls.begin(); it != drawCalls.end(); ++it) {
            switch (it->element) {
			case DrawElement::LINE:
				_drawLine(it->start, it->end, it->color);
				break;
			case DrawElement::RAY:
				_drawRay(it->start, it->dir, it->color);
				break;
			case DrawElement::CIRCLE:
				_drawCircle(it->position, it->radius, it->color, it->mode);
				break;
			case DrawElement::POINT:
				_drawPoint(it->position, it->color, it->tickness);
				break;
			case DrawElement::POLYGON:
				_drawPolygon(it->vertices, it->color, it->mode);
				break;
			case DrawElement::VECTOR:
				break;
            }
            if (it->duration > 0.0f && it->expire == 0.0f) it->expire = Time::time + it->duration;
		}
	}

	//{ #region draw methods

	void Design::DrawLine(glm::vec3 start, glm::vec3 end, Color color, float duration) {
		DrawCall call;
		call.element = DrawElement::LINE;
		call.mode = DrawMode::HOLLOW;
		call.start = start;
		call.end = end;
		call.color = color;
		call.duration = duration;

		AddDrawCall(call);
	}

	void Design::DrawPoint(glm::vec3 position, Color color, float duration) {
		DrawCall call;
		call.element = DrawElement::POINT;
		call.mode = DrawMode::HOLLOW;
		call.position = position;
		call.color = color;
		call.duration = duration;

		AddDrawCall(call);
	}

	void Design::DrawPoint(glm::vec3 position, Color color, int tickness, float duration) {
		DrawCall call;
		call.element = DrawElement::POINT;
		call.mode = DrawMode::HOLLOW;
		call.position = position;
		call.color = color;
		call.duration = duration;
		call.tickness = tickness;

		AddDrawCall(call);
	}


	void Design::DrawRay(glm::vec3 start, glm::vec3 dir, Color color, float duration) {
		DrawCall call;
		call.element = DrawElement::RAY;
		call.mode = DrawMode::HOLLOW;
		call.start = start;
		call.dir = dir;
		call.color = color;
		call.duration = duration;

		AddDrawCall(call);
	}

	void Design::DrawPolygon(std::vector<glm::vec3> vertices, Color color, DrawMode mode, float duration) {
		DrawCall call;
		call.element = DrawElement::POLYGON;
		call.mode = mode;
		call.vertices = vertices;
		call.color = color;
		call.duration = duration;

		AddDrawCall(call);
	}

	void Design::DrawCircle(glm::vec3 position, float radius, Color color, DrawMode mode, float duration) {
		DrawCall call;
		call.element = DrawElement::CIRCLE;
		call.mode = mode;
		call.position = position;
		call.radius = radius;
		call.color = color;
		call.duration = duration;

		AddDrawCall(call);
	}

	void Design::_drawPoint(glm::vec3 position, Color color, int tickness) {
		if (!initDraw()) return;

		vertices = {position};

		initVAO();

		setColor(color);
		glPointSize(tickness);
		glDrawArrays(GL_POINTS, 0, 1);
		glPointSize(1);
		closeVAO();
	}

	void Design::_drawLine(glm::vec3 start, glm::vec3 end, Color color) {
		if (!initDraw()) return;

		vertices = {start, end};

		initVAO();

		setColor(color);
		glDrawArrays(GL_LINES, 0, vertices.size());

		closeVAO();
	}

	void Design::_drawRay(glm::vec3 start, glm::vec3 dir, Color color) {
		if (!initDraw()) return;

		vertices = {start, start + dir};

		initVAO();

		setColor(color);
		glDrawArrays(GL_LINES, 0, vertices.size());

		closeVAO();
	}

	void Design::_drawPolygon(std::vector<glm::vec3> vertices_, Color color, DrawMode mode) {
		if (!initDraw()) return;

		vertices.swap(vertices_);

		initVAO();

		setColor(color);
		glDrawArrays((mode == DrawMode::HOLLOW ? GL_LINE_LOOP : GL_TRIANGLE_FAN), 0, vertices.size());

		closeVAO();
	}

	void Design::_drawCircle(glm::vec3 position, float radius, Color color, DrawMode mode) {
		if (!initDraw()) return;

		vertices.clear();
		int NUM_DIVISIONS = 31;

		for(int i = 0; i < NUM_DIVISIONS +1; i++) {
			if (mode == DrawMode::FULL) if (i % 3 == 0) vertices.push_back({position.x,  position.y, 0.0f});
			vertices.push_back({position.x + radius * cos((float) i / NUM_DIVISIONS * M_PI * 2), position.y + radius * sin((float) i / NUM_DIVISIONS * M_PI * 2), 0.0f});
		}

		initVAO();

		setColor(color);
		glDrawArrays((mode == DrawMode::FULL ? GL_TRIANGLE_STRIP : GL_LINE_LOOP), 0, vertices.size());

		closeVAO();
	}

	//}

	void Design::initVAO() {
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

	void Design::closeVAO() {
		glDisablei(GL_BLEND, vertexBuffer);
		glUseProgram(0);
		glBindVertexArray(0);
	}

	void Design::setColor(Color color) {
		glUniform4f(glGetUniformLocation(shader->GetProgram(), "renderer_color"), color.r, color.g, color.b, color.a);
	}

	//init

	Shader* Design::shader = nullptr;
	bool Design::readyToDraw;
	GLuint Design::VAO;
	GLuint Design::vertexBuffer;
	std::vector<glm::vec3> Design::vertices;
	std::vector<DrawCall> Design::drawCalls;
}
