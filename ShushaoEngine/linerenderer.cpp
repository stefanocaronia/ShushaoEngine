#include "linerenderer.h"
#include "libs.h"
#include "transform.h"
#include "color.h"
#include "debug.h"

#include <vector>
#include <glm.hpp>

namespace ShushaoEngine {

	using namespace std;
	using namespace glm;

	LineRenderer::LineRenderer() {
		name = "Line Renderer";
	}


	LineRenderer::~LineRenderer() {
		name = "Line Renderer";
	}

	LineRenderer::LineRenderer(string n) {
		name = n;
	}

	void LineRenderer::AddLine(const vec3 start_point, const vec3 end_point, Color col) {
		vertices.push_back(start_point);
		vertices.push_back(end_point);
		colors.push_back(col);
		colors.push_back(col);
	}

	void LineRenderer::AddPolyline(const vector<vec3> points, Color col) {
		bool isFirst = true;
		vec3 lastpoint;
		for (vec3 point : points) {
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

	void LineRenderer::init() {
		Debug::Log(INFO, "In Init di Line Renderer");
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

	void LineRenderer::render() {

		glBindVertexArray(VAO);
		glUseProgram(shader->getProgram());

		// uniforms
		glUniform4f(glGetUniformLocation(shader->getProgram(), "renderer_color"), color.r, color.g, color.b, color.a);
		glUniformMatrix4fv(glGetUniformLocation(shader->getProgram(), "MVP"), 1, GL_FALSE, &transform->MVP[0][0]);

		glEnablei(GL_BLEND, vertexBuffer);

		glDrawArrays(GL_LINES, 0, vertices.size());

		glDisablei(GL_BLEND, vertexBuffer);

		glUseProgram(0);
		glBindVertexArray(0);
	}

	void LineRenderer::exit() {

		glUseProgram(0);
		glDisableVertexAttribArray(0);
		glBindVertexArray(0);
	}


}
