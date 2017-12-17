#include "design.h"
#include "glmanager.h"
#include "scenemanager.h"

namespace ShushaoEngine {

	bool Design::initDraw() {
		if (readyToDraw) return true;
		if (!GLManager::ready) return false;

		shader = new Shader();

		shader->LoadFromString(R"(
			#version 330 core
			layout(location=0) in vec3 position;
			uniform mat4 MVP;

			void main() {
				gl_Position = MVP * vec4(position, 1.0);
			}
		)", R"(
			#version 330 core
			uniform vec4 renderer_color;

			out vec4 out_color;

			void main() {
				out_color = vec4(renderer_color);
			}
		)");

		vertices.reserve(256);
		return readyToDraw = true;
	}

	void Design::DrawLine(glm::vec3 start, glm::vec3 end, Color color) {
		if (!initDraw()) return;

		vertices = {start, end};

		initVAO();

		setColor(color);
		glDrawArrays(GL_LINES, 0, vertices.size());

		closeVAO();
	}

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
}
