#include <vector>
#include <glm/glm.hpp>

#include "linerenderer.h"
#include "transform.h"
#include "color.h"
#include "shader.h"

namespace se {

	LineRenderer::LineRenderer() {
		name = "Line Renderer";

		shader = new Shader();
		shader->LoadFromString(
			#include "wire.vert"
			,
			#include "wire.frag"
		);
		shader->name = "Wireframe";
	}

	LineRenderer::~LineRenderer() {
		name = "Line Renderer";

		if (shader != nullptr) delete(shader);
	}

	LineRenderer::LineRenderer(std::string n) {
		name = n;
	}

	void LineRenderer::AddLine(const glm::vec3 start_point, const glm::vec3 end_point, Color col) {
		vertices.push_back(start_point);
		vertices.push_back(end_point);
		colors.push_back(col);
		colors.push_back(col);
	}

	void LineRenderer::AddPolyline(const std::vector<glm::vec3> points, Color col) {
		bool isFirst = true;
		glm::vec3 lastpoint;
		for (glm::vec3 point : points) {
			if (!isFirst) {
				vertices.push_back(lastpoint);
				colors.push_back(col);
			}
			vertices.push_back(point);
			colors.push_back(col);
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
                    colors.push_back(color);
			}
			vertices.push_back({position.x + radius * cos((float) i / NUM_DIVISIONS * M_PI * 2), position.y + radius * sin((float) i / NUM_DIVISIONS * M_PI * 2), 0.0f});
			colors.push_back(color);
		}
	}

	void LineRenderer::Awake() {

		using namespace glm;

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3), &vertices[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenBuffers(1, &colorBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
		glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(vec4), &colors[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glVertexAttribPointer(ShaderLocation::POSITION, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(ShaderLocation::POSITION);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
		glVertexAttribPointer(ShaderLocation::COLOR, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(ShaderLocation::COLOR);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);
	}

	void LineRenderer::Render() {

		glBindVertexArray(VAO);
		glUseProgram(shader->GetProgram());

		// uniforms
		glUniform4f(glGetUniformLocation(shader->GetProgram(), "renderer_color"), color.r, color.g, color.b, color.a);
		glUniformMatrix4fv(glGetUniformLocation(shader->GetProgram(), "MVP"), 1, GL_FALSE, &transform->MVP[0][0]);

		glEnablei(GL_BLEND, vertexBuffer);

		glDrawArrays(GL_LINES, 0, vertices.size());

		glDisablei(GL_BLEND, vertexBuffer);

		glUseProgram(0);
		glBindVertexArray(0);
	}

	void LineRenderer::OnDestroy() {

		glUseProgram(0);
		glDisableVertexAttribArray(0);
		glBindVertexArray(0);
	}


}
