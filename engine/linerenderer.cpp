#include <vector>
#include <glm/glm.hpp>

#include "linerenderer.h"
#include "transform.h"
#include "color.h"
#include "shader.h"

namespace se {

	using namespace glm;

	LineRenderer::LineRenderer() {
		name = "Line Renderer";

		shader = new Shader();
		shader->LoadFromString(
			#include "wire.vert"
			,
			#include "wire.frag"
		);
		shader->name = "Wireframe";

		VAO = new Vao(GL_DYNAMIC_DRAW);
	}

	LineRenderer::~LineRenderer() {
		name = "Line Renderer";

		if (shader != nullptr) { delete(shader); shader = nullptr; }
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

		VAO->SetVertices(vertices);
		VAO->SetColors(colors);
	}

	void LineRenderer::Update() {}

	void LineRenderer::Render() {

		VAO->Bind();
		shader->Use();

		shader->SetMatrix("MVP", transform->uMVP());
		shader->update();

		glEnablei(GL_BLEND, VAO->vertexBuffer);
		glDrawArrays(GL_LINES, 0, vertices.size());
		glDisablei(GL_BLEND, VAO->vertexBuffer);

		shader->Leave();
		VAO->Unbind();
	}

	void LineRenderer::OnDestroy() {

		shader->Leave();
		VAO->Unbind();
	}
}
