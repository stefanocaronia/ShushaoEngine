#include <vector>
#include <glm/glm.hpp>

#include "glmanager.h"
#include "geometryrenderer.h"
#include "transform.h"
#include "color.h"
#include "shaders/wireframeshader.h"

namespace se {

	using namespace glm;

	void GeometryRenderer::setup() {
		shader = new WireframeShader();
	}

	GeometryRenderer::~GeometryRenderer() {
		if (VAO != nullptr) { delete(VAO); VAO = nullptr; }
	}

	void GeometryRenderer::AddLine(const glm::vec3 start_point, const glm::vec3 end_point, Color col) {
		vertices.push_back(start_point);
		vertices.push_back(end_point);
		colors.push_back(col.rgba());
		colors.push_back(col.rgba());
	}

	void GeometryRenderer::AddPolyline(const std::vector<glm::vec3> points, Color col) {
		bool isFirst = true;
		glm::vec3 lastpoint;
		for (glm::vec3 point : points) {
			if (!isFirst) {
				vertices.push_back(lastpoint);
				colors.push_back(col.rgba());
			}
			vertices.push_back(point);
			colors.push_back(col.rgba());
			isFirst = false;
			lastpoint = point;
		}
	}

    void GeometryRenderer::AddCircle(glm::vec3 position, float radius, Color color, DrawMode mode) {

        // TODO: non funziona molto

		int NUM_DIVISIONS = 120;

		for(int i = 0; i < NUM_DIVISIONS +1; i++) {
			if (mode == DrawMode::FULL) if (i % 3 == 0) {
                    vertices.push_back({position.x,  position.y, 0.0f});
                    colors.push_back(color.rgba());
			}
			vertices.push_back({position.x + radius * cos((float) i / NUM_DIVISIONS * M_PI * 2), position.y + radius * sin((float) i / NUM_DIVISIONS * M_PI * 2), 0.0f});
			colors.push_back(color.rgba());
		}
	}

	void GeometryRenderer::Awake() {

		shader->awake();
		shader->Use();

		VAO = new Vao();
		VAO->AddBuffer(Vbo::VERTICES, VBO_CONFIG_VERTEX);
		VAO->AddBuffer("colors", VBO_CONFIG_COLOR);
		VAO->Init();

		VAO->Use();
		VAO->Load<vec3>(Vbo::VERTICES, vertices);
		VAO->Load<vec4>("colors", colors);
		VAO->Leave();

		shader->Leave();
	}

	void GeometryRenderer::Update() {}

	void GeometryRenderer::Render() {

		shader->Use();
		VAO->Use();

		shader->SetMVP(transform->uMVP());
		shader->update();

		if (renderMode == RenderMode::SCREEN) {
			shader->SetM(transform->uM());
			shader->Enable("viewport");
			shader->SetVector("viewport", GLManager::VIEWPORT);
		}

		glEnablei(GL_BLEND, VAO->GetBuffer(Vbo::VERTICES)->Id);
		glDrawArrays(GL_LINES, 0, vertices.size());
		glDisablei(GL_BLEND, VAO->GetBuffer(Vbo::VERTICES)->Id);

		if (renderMode == RenderMode::SCREEN) {
			shader->Disable("viewport");
		}

		VAO->Leave();
		shader->Use();
	}

	void GeometryRenderer::OnDestroy() {

		shader->Leave();
		VAO->Leave();
	}
}
