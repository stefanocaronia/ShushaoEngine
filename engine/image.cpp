#include <iostream>
#include <glm/glm.hpp>

#include "debug.h"
#include "sprite.h"
#include "image.h"
#include "transform.h"
#include "shaders/standardshader.h"
#include "entity.h"

namespace se {

	using namespace std;
	using namespace glm;

	void Image::setup() {
		entity->transform->isRectTransform = true;
		material = new Material();
		material->SetShader(new StandardShader());
		transform->SetPivot(PivotPosition::TOPLEFT);

		VAO = new Vao();
		VAO->AddBuffer(Vbo::VERTICES, VBO_CONFIG_VERTEX);
		VAO->AddBuffer(Vbo::UV, VBO_CONFIG_UV);
		VAO->AddBuffer(Vbo::NORMALS, VBO_CONFIG_NORMAL);
		VAO->AddBuffer(Vbo::INDEXES, VBO_CONFIG_INDEX);
		VAO->Init();
	}

	Image::~Image() {
		if (material != nullptr) delete(material);
		delete(VAO);
		VAO = nullptr;
	}

	bool Image::isReady() {
		return (
			material != nullptr &&
			material->shader != nullptr &&
			transform != nullptr
		);
	}

	void Image::Awake() {
		if (texture != nullptr) {
			material->SetMainTexture(texture);
		}
	}

	void Image::Update() {
		if (!isReady()) return;

		Build();
	}

	void Image::Render() {

		if (!isReady()) return;

		VAO->Use();
		material->shader->Use();
		material->shader->SetRenderColor(material->color);
		material->shader->SetMVP(transform->uMVP());
		material->update();

		VAO->GetBuffer(Vbo::INDEXES)->Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
		VAO->GetBuffer(Vbo::INDEXES)->Unbind();

		material->shader->Leave();
		VAO->Leave();
	}

	void Image::OnDestroy() {

		if (!isReady()) return;

		VAO->Leave();
		material->shader->Leave();
		material->shader->exit();
		delete(material);
		material = nullptr;
	}

	Image* Image::Build() {
		Rect rect = entity->transform->rectTransform->rect;
		GLfloat wX = (rect.width / 2);
		GLfloat wY = (rect.height / 2);

		vertices.clear();
		vertices = {
			{-wX, -wY, 0.0f}, // Bottom-left
			{ wX, -wY, 0.0f}, // Bottom-right
			{ wX,  wY, 0.0f}, // Top-right
			{-wX,  wY, 0.0f} // Top-left
		};

		if (rect.width < texture->width || rect.height < texture->height) {

			// rect in texture coord
			Rect tsr(
				rect.x / texture->width,
				rect.y / texture->height,
				rect.width / texture->width,
				rect.height / texture->height
			);

			uv = { // The base texture coordinates of the sprite mesh.
				{tsr.x, tsr.yMax}, // Bottom-left of texture
				{tsr.xMax, tsr.yMax}, // Bottom-right of texture
				{tsr.xMax, tsr.y}, // Top-Right of texture
				{tsr.x, tsr.y} // Top-left of texture
			};
		}

		VAO->Use();
		VAO->Load<vec3>(Vbo::VERTICES, vertices);
		VAO->Load<vec2>(Vbo::UV, uv);
		VAO->Load<vec3>(Vbo::NORMALS, normals);
		VAO->Load<GLushort>(Vbo::INDEXES, indexes);
		VAO->Leave();

		return this;
	}
}
