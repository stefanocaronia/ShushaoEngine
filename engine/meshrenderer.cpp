#include <iostream>

#include "debug.h"
#include "mesh.h"
#include "color.h"
#include "meshrenderer.h"
#include "meshshader.h"
#include "transform.h"
#include "glmanager.h"
#include "meshshader.h"

namespace se {

	MeshRenderer::MeshRenderer() {
		name = "Mesh Renderer";
		material = new Material();
		material->SetShader(GLManager::GetShader<MeshShader>());
	}

	MeshRenderer::~MeshRenderer() {
		if (material != nullptr) delete(material);
	}

	MeshRenderer::MeshRenderer(string n) {
		name = n;
	}

	bool MeshRenderer::isReady() {
		return (
			mesh != nullptr &&
			material != nullptr &&
			material->shader != nullptr &&
			transform != nullptr
		);
	}

	void MeshRenderer::Awake() {

		if (mesh == nullptr) {
			Debug::Log(ERROR) << "Mesh undefined" << endl;
			return;
		}

		if (mesh->VAO == nullptr) {
			Debug::Log(ERROR) << "Mesh VAO undefined" << endl;
			return;
		}

		material->init();
	}

	void MeshRenderer::Update() {
		if (!isReady()) return;
	}

	void MeshRenderer::Render() {

		if (!isReady()) return;

		mesh->VAO->Use();
		material->shader->Use();
		material->shader->SetMVP(transform->uMVP());
		material->shader->SetRenderColor(material->color);
		material->update();

		glActiveTexture(GL_TEXTURE0);
		//glActiveTexture(material->shader->GetTexture("diffuse_map"));
		glBindTexture(GL_TEXTURE_2D, material->mainTexture->TextureID);
		glDrawArrays(GL_TRIANGLES, 0, mesh->VAO->GetBuffer("vertex")->size * 3);
		//glDrawElements(GL_TRIANGLES, mesh->VAO->GetBuffer("index")->size, GL_UNSIGNED_SHORT, 0);
		glBindTexture(GL_TEXTURE_2D, 0);

		material->shader->Leave();
		mesh->VAO->Leave();
	}

	void MeshRenderer::OnDestroy() {

		if (!isReady()) return;

		mesh->VAO->Leave();
		material->shader->Leave();
		material->shader->exit();
		delete(material);
		material = nullptr;
	}
}
