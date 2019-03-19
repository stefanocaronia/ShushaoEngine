#include "debug.h"
#include "design.h"
#include "glmanager.h"
#include "scenemanager.h"
#include "shaders/baseshader.h"

namespace se {

	using namespace std;
	using namespace glm;

	bool Design::Init() {
		if (ready) return true;
		if (!GLManager::ready) return false;

		shader = new BaseShader();
		shader->awake();
		shader->Use();

		VAO = new Vao();
		VAO->AddBuffer(Vbo::VERTICES, VBO_CONFIG_VERTEX);
		VAO->Init();

		return ready = true;
	}

	void Design::Clear() {
		drawCalls.clear();
		if (shader != nullptr) delete(shader);
	}

	//{ #region draw calls

	void Design::AddDrawCall(DrawCall call) {
		auto it = std::find(drawCalls.begin(), drawCalls.end(), call);
		if (it == drawCalls.end()) {
			 drawCalls.push_back(call);
		}
	}

	void Design::ProcessDrawCalls() {

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
					_drawPolygon(it->vertices, it->color, it->mode, it->renderMode, it->MVP);
					break;
				case DrawElement::VECTOR:
					_drawVector(it->start, it->end, it->color, it->normalized, it->renderMode, it->MVP);
					break;
            }

            if (it->duration > 0.0f && it->expire == 0.0f) it->expire = Time::time + it->duration;
		}

		drawCalls.erase(std::remove_if(drawCalls.begin(), drawCalls.end(), [=](DrawCall& c) {
			return (c.duration == 0.0f || (c.duration > 0.0f && c.expire > 0.0f && Time::time > c.expire));
		}), drawCalls.end());
	}

	void Design::DrawLine(glm::vec3 start, glm::vec3 end, Color color, glm::mat4 mvp, float duration) {
		DrawCall call;
		call.element = DrawElement::LINE;
		call.mode = DrawMode::HOLLOW;
		call.start = start;
		call.end = end;
		call.color = color;
		call.duration = duration;
		call.MVP = mvp;

		AddDrawCall(call);
	}

	void Design::DrawVector(glm::vec3 start, glm::vec3 end, Color color, bool normalized, RenderMode renderMode, glm::mat4 mvp, float duration) {
		DrawCall call;
		call.element = DrawElement::VECTOR;
		call.start = start;
		call.end = end;
		call.normalized = normalized;
		call.color = color;
		call.duration = duration;
		call.renderMode = renderMode;
		call.MVP = mvp;

		AddDrawCall(call);
	}

	void Design::DrawPoint(glm::vec3 position, Color color, glm::mat4 mvp, float duration) {
		DrawCall call;
		call.element = DrawElement::POINT;
		call.mode = DrawMode::HOLLOW;
		call.position = position;
		call.color = color;
		call.duration = duration;
		call.MVP = mvp;

		AddDrawCall(call);
	}

	void Design::DrawPoint(glm::vec3 position, Color color, int tickness, glm::mat4 mvp, float duration) {
		DrawCall call;
		call.element = DrawElement::POINT;
		call.mode = DrawMode::HOLLOW;
		call.position = position;
		call.color = color;
		call.duration = duration;
		call.tickness = tickness;
		call.MVP = mvp;

		AddDrawCall(call);
	}

	void Design::DrawRay(glm::vec3 start, glm::vec3 dir, Color color, glm::mat4 mvp, float duration) {
		DrawCall call;
		call.element = DrawElement::RAY;
		call.mode = DrawMode::HOLLOW;
		call.start = start;
		call.dir = dir;
		call.color = color;
		call.duration = duration;
		call.MVP = mvp;

		AddDrawCall(call);
	}

	void Design::DrawPolygon(std::vector<glm::vec3> vertices, Color color, DrawMode mode, RenderMode renderMode, glm::mat4 mvp, float duration) {
		DrawCall call;
		call.element = DrawElement::POLYGON;
		call.mode = mode;
		call.vertices = vertices;
		call.color = color;
		call.duration = duration;
		call.renderMode = renderMode;
		call.MVP = mvp;

		AddDrawCall(call);
	}

	void Design::DrawCircle(glm::vec3 position, float radius, Color color, DrawMode mode, glm::mat4 mvp, float duration) {
		DrawCall call;
		call.element = DrawElement::CIRCLE;
		call.mode = mode;
		call.position = position;
		call.radius = radius;
		call.color = color;
		call.duration = duration;
		call.MVP = mvp;

		AddDrawCall(call);
	}

	void Design::DrawRect(glm::vec3 position, Rect rect, Color color, DrawMode mode, RenderMode renderMode, glm::mat4 mvp, float duration) {

		rect.SetX(rect.x + position.x);
		rect.SetY(rect.y + position.y);
		DrawCall call;
		call.element = DrawElement::POLYGON;
		call.mode = mode;
		call.vertices = rect.GetVertices3D();
		call.color = color;
		call.duration = duration;
		call.renderMode = renderMode;
		call.MVP = mvp;

		AddDrawCall(call);
	}

	//}

	//{ #region draw methods

	void Design::_drawPoint(glm::vec3 position, Color color, int tickness, RenderMode renderMode, glm::mat4 mvp) {
		if (!Init()) return;

		vertices.clear();
		vertices = {position};

		shader->Use();
		VAO->Use();
		VAO->Load<vec3>(Vbo::VERTICES, vertices);

		if (mvp == Transform::MAT4_IDENTITY || renderMode == RenderMode::SCREEN)
			mvp = SceneManager::activeScene->activeCamera->Projection * SceneManager::activeScene->activeCamera->getViewMatrix() * glm::mat4();

		if (renderMode == RenderMode::SCREEN) {
			shader->Enable("viewport");
			shader->SetVector("viewport", GLManager::VIEWPORT);
		}

		shader->SetMVP(&mvp[0][0]);
		shader->SetRenderColor(color);

		VAO->GetBuffer(Vbo::VERTICES)->Bind();

		glEnablei(GL_BLEND, VAO->GetBuffer(Vbo::VERTICES)->Id);
		glPointSize(tickness);
		glDrawArrays(GL_POINTS, 0, 1);
		glPointSize(1);
		glDisablei(GL_BLEND, VAO->GetBuffer(Vbo::VERTICES)->Id);

		VAO->GetBuffer(Vbo::VERTICES)->Unbind();

		if (renderMode == RenderMode::SCREEN) {
			shader->Disable("viewport");
		}

		VAO->Leave();
		shader->Leave();
	}

	void Design::_drawLine(glm::vec3 start, glm::vec3 end, Color color, RenderMode renderMode, glm::mat4 mvp) {
		if (!Init()) return;

		vector<glm::vec3> vertices = {start, end};

		shader->Use();
		VAO->Use();
		VAO->Load<vec3>(Vbo::VERTICES, vertices);

		if (mvp == Transform::MAT4_IDENTITY || renderMode == RenderMode::SCREEN)
			mvp = SceneManager::activeScene->activeCamera->Projection * SceneManager::activeScene->activeCamera->getViewMatrix() * glm::mat4();

		if (renderMode == RenderMode::SCREEN) {
			shader->Enable("viewport");
			shader->SetVector("viewport", GLManager::VIEWPORT);
		}

		shader->SetMVP(&mvp[0][0]);
		shader->SetRenderColor(color);

		glEnablei(GL_BLEND, VAO->GetBuffer(Vbo::VERTICES)->Id);
		glDrawArrays(GL_LINES, 0, vertices.size());
		glDisablei(GL_BLEND, VAO->GetBuffer(Vbo::VERTICES)->Id);

		if (renderMode == RenderMode::SCREEN) {
			shader->Disable("viewport");
		}

		VAO->Leave();
		shader->Leave();
	}

	void Design::_drawVector(glm::vec3 start, glm::vec3 end, Color color, bool normalized, RenderMode renderMode, glm::mat4 mvp) {
		if (!Init()) return;

		GLfloat bxs = 0.02f;
		if (normalized) end = normalize(end);
		vector<vec3> vertices = {
			vec3( -bxs,  -bxs, 0.0f) + start,
			vec3( -bxs,  bxs, 0.0f) + start,
			vec3( bxs,  bxs, 0.0f) + start,
			vec3( bxs,  -bxs, 0.0f) + start,
			vec3( -bxs,  -bxs, 0.0f) + start,
			start,
			start + end,
			start
		};

		shader->Use();
		VAO->Use();
		VAO->Load<vec3>(Vbo::VERTICES, vertices);

		if (mvp == Transform::MAT4_IDENTITY || renderMode == RenderMode::SCREEN)
			mvp = SceneManager::activeScene->activeCamera->Projection * SceneManager::activeScene->activeCamera->getViewMatrix() * glm::mat4();

		shader->SetMVP(&mvp[0][0]);
		shader->SetRenderColor(color);

		if (renderMode == RenderMode::SCREEN) {
			shader->Enable("viewport");
			shader->SetVector("viewport", GLManager::VIEWPORT);
		}

		glEnablei(GL_BLEND, VAO->GetBuffer(Vbo::VERTICES)->Id);
		glPointSize(2);
		glDrawArrays(GL_LINE_LOOP, 0, vertices.size());
		glPointSize(1);
		glDisablei(GL_BLEND, VAO->GetBuffer(Vbo::VERTICES)->Id);

		if (renderMode == RenderMode::SCREEN) {
			shader->Disable("viewport");
		}

		VAO->Leave();
		shader->Leave();
	}

	void Design::_drawRay(glm::vec3 start, glm::vec3 dir, Color color, RenderMode renderMode, glm::mat4 mvp) {
		if (!Init()) return;

		vector<glm::vec3> vertices = {start, start + dir};

		shader->Use();
		VAO->Use();
		VAO->Load<vec3>(Vbo::VERTICES, vertices);

		if (mvp == Transform::MAT4_IDENTITY || renderMode == RenderMode::SCREEN)
			mvp = SceneManager::activeScene->activeCamera->Projection * SceneManager::activeScene->activeCamera->getViewMatrix() * glm::mat4();

		if (renderMode == RenderMode::SCREEN) {
			shader->Enable("viewport");
			shader->SetVector("viewport", GLManager::VIEWPORT);
		}

		shader->SetMVP(&mvp[0][0]);
		shader->SetRenderColor(color);

		glEnablei(GL_BLEND, VAO->GetBuffer(Vbo::VERTICES)->Id);
		glDrawArrays(GL_LINES, 0, vertices.size());
		glDisablei(GL_BLEND, VAO->GetBuffer(Vbo::VERTICES)->Id);

		if (renderMode == RenderMode::SCREEN) {
			shader->Disable("viewport");
		}

		VAO->Leave();
		shader->Leave();
	}

	void Design::_drawPolygon(std::vector<glm::vec3> vertices, Color color, DrawMode mode, RenderMode renderMode, glm::mat4 mvp) {
		if (!Init()) return;

		shader->Use();
		VAO->Use();

		VAO->Load<vec3>(Vbo::VERTICES, vertices);

		if (mvp == Transform::MAT4_IDENTITY || renderMode == RenderMode::SCREEN) {
			mvp = SceneManager::activeScene->activeCamera->Projection * SceneManager::activeScene->activeCamera->getViewMatrix() * glm::mat4();
		}

		shader->SetMVP(&mvp[0][0]);

		if (renderMode == RenderMode::SCREEN) {
			shader->Enable("viewport");
			shader->SetVector("viewport", GLManager::VIEWPORT);
		}

		VAO->GetBuffer(Vbo::VERTICES)->Bind();
		glEnablei(GL_BLEND, VAO->GetBuffer(Vbo::VERTICES)->Id);

		if (mode == DrawMode::BORDERED)
			shader->SetRenderColor({color.r, color.g, color.b, color.a / 2});
		else
			shader->SetRenderColor(color);
		if (mode == DrawMode::HOLLOW) glLineWidth(2);
		glDrawArrays((mode != DrawMode::HOLLOW ? GL_TRIANGLE_FAN : GL_LINE_LOOP), 0, vertices.size());


		if (mode == DrawMode::BORDERED) {
			glLineWidth(2);
			shader->SetRenderColor(color);
			glDrawArrays(GL_LINE_LOOP, 0, vertices.size());
			glLineWidth(1);
		}

		glDisablei(GL_BLEND, VAO->GetBuffer(Vbo::VERTICES)->Id);
		glLineWidth(1);
		VAO->GetBuffer(Vbo::VERTICES)->Unbind();

		if (renderMode == RenderMode::SCREEN) {
			shader->Disable("viewport");
		}

		VAO->Leave();
		shader->Leave();
	}

	void Design::_drawCircle(glm::vec3 position, float radius, Color color, DrawMode mode, RenderMode renderMode, glm::mat4 mvp) {
		if (!Init()) return;

		vector<glm::vec3> vertices;
		int NUM_DIVISIONS = 31;

		for(int i = 0; i < NUM_DIVISIONS +1; i++) {
			if (mode == DrawMode::FULL) if (i % 3 == 0) vertices.push_back({position.x,  position.y, 0.0f});
			vertices.push_back({position.x + radius * cos((float) i / NUM_DIVISIONS * M_PI * 2), position.y + radius * sin((float) i / NUM_DIVISIONS * M_PI * 2), 0.0f});
		}

		shader->Use();
		VAO->Use();

		VAO->Load<vec3>(Vbo::VERTICES, vertices);

		if (mvp == Transform::MAT4_IDENTITY || renderMode == RenderMode::SCREEN) {
			mvp = SceneManager::activeScene->activeCamera->Projection * SceneManager::activeScene->activeCamera->getViewMatrix() * glm::mat4();
		}

		shader->SetMVP(&mvp[0][0]);
		shader->SetRenderColor(color);

		if (renderMode == RenderMode::SCREEN) {
			shader->Enable("viewport");
			shader->SetVector("viewport", GLManager::VIEWPORT);
		}

		glEnablei(GL_BLEND, VAO->GetBuffer(Vbo::VERTICES)->Id);
		glDrawArrays((mode == DrawMode::FULL ? GL_TRIANGLE_STRIP : GL_LINE_LOOP), 0, vertices.size());
		glDisablei(GL_BLEND, VAO->GetBuffer(Vbo::VERTICES)->Id);


		if (renderMode == RenderMode::SCREEN) {
			shader->Disable("viewport");
		}

		VAO->Leave();
		shader->Leave();
	}

	//}

	// init
	Shader* Design::shader = nullptr;
	bool Design::ready;
	Vao* Design::VAO;
	std::vector<glm::vec3> Design::vertices;
	std::vector<DrawCall> Design::drawCalls;
}
