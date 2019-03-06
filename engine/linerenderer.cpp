#include <vector>
#include <glm/glm.hpp>

#include "glmanager.h"
#include "linerenderer.h"
#include "transform.h"
#include "color.h"
#include "wireframeshader.h"

namespace se {

	using namespace glm;

	LineRenderer::LineRenderer() {
		name = "Line Renderer";

		shader = GLManager::GetShader<WireframeShader>();


	}

	LineRenderer::~LineRenderer() {
		name = "Line Renderer";
		if (VAO != nullptr) { delete(VAO); VAO = nullptr; }
	}

	LineRenderer::LineRenderer(std::string n) {
		name = n;
	}

	void LineRenderer::AddLine(const glm::vec3 start_point, const glm::vec3 end_point, Color col) {
		vertices.push_back(start_point);
		vertices.push_back(end_point);
		colors.push_back(col.rgba);
		colors.push_back(col.rgba);
	}

	void LineRenderer::AddPolyline(const std::vector<glm::vec3> points, Color col) {
		bool isFirst = true;
		glm::vec3 lastpoint;
		for (glm::vec3 point : points) {
			if (!isFirst) {
				vertices.push_back(lastpoint);
				colors.push_back(col.rgba);
			}
			vertices.push_back(point);
			colors.push_back(col.rgba);
			isFirst = false;
			lastpoint = point;
		}
	}

    void LineRenderer::AddCircle(glm::vec3 position, float radius, Color color, DrawMode mode) {

        // TODO: non funziona molto

		int NUM_DIVISIONS = 120;

		for(int i = 0; i < NUM_DIVISIONS +1; i++) {
			if (mode == DrawMode::FULL) if (i % 3 == 0) {
                    vertices.push_back({position.x,  position.y, 0.0f});
                    colors.push_back(color.rgba);
			}
			vertices.push_back({position.x + radius * cos((float) i / NUM_DIVISIONS * M_PI * 2), position.y + radius * sin((float) i / NUM_DIVISIONS * M_PI * 2), 0.0f});
			colors.push_back(color.rgba);
		}
	}

	void LineRenderer::Awake() {

		shader->awake();
		shader->Use();

		VAO = new Vao();
		VAO->AddBuffer("vertex", VBO_CONFIG_VERTEX);
		VAO->AddBuffer("colors", VBO_CONFIG_COLOR);
		VAO->Init();

		VAO->Use();
		VAO->Load<vec3>("vertex", vertices);
		VAO->Load<vec4>("colors", colors);
		VAO->Leave();

		shader->Leave();
	}

	void LineRenderer::Update() {}

	void LineRenderer::Render() {

		shader->Use();
		VAO->Use();

		shader->SetMVP(transform->uMVP());
		shader->update();

		glEnablei(GL_BLEND, VAO->GetBuffer("vertex")->Id);
		glDrawArrays(GL_LINES, 0, vertices.size());
		glDisablei(GL_BLEND, VAO->GetBuffer("vertex")->Id);

		VAO->Leave();
		shader->Use();
	}

	void LineRenderer::OnDestroy() {

		shader->Leave();
		VAO->Leave();
	}
}
