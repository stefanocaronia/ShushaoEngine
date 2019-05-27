
#include <glad/glad.h>

#include "Core.h"
#include "sepch.h"
#include "Debug.h"
#include "Entity.h"
#include "RawImage.h"
#include "Shaders/StandardShader.h"
#include "Transform.h"

namespace se {

void RawImage::setup() {
    entity->transform->isRectTransform = true;
    material = new Material();
    material->SetShader(new StandardShader());
    transform->SetPivot(PivotPosition::CENTER);

    VAO = new Vao();
    VAO->AddBuffer(Vbo::VERTICES, VBO_CONFIG_VERTEX);
    VAO->AddBuffer(Vbo::UV, VBO_CONFIG_UV);
    VAO->AddBuffer(Vbo::NORMALS, VBO_CONFIG_NORMAL);
    VAO->AddBuffer(Vbo::INDEXES, VBO_CONFIG_INDEX);
    VAO->Init();
}

RawImage::~RawImage() {
    if (material != nullptr) delete (material);
    delete (VAO);
    VAO = nullptr;
}

RawImage* RawImage::SetUvRect(Rect rect_) {
    uvRect = rect_;
    uvRect.YUP = true;

    uv = {
        uvRect.bottomleft,  // Bottom-left of texture
        uvRect.bottomright,  // Bottom-right of texture
        uvRect.topright,  // Top-Right of texture
        uvRect.topleft  // Top-left of texture
    };

    return this;
}

RawImage* RawImage::SetColor(Color color_) {
    color = color_;
    material->color = color;

    return this;
}

bool RawImage::isReady() {
    return (
        material != nullptr &&
        material->shader != nullptr &&
        transform != nullptr);
}

void RawImage::Awake() {
    if (texture != nullptr) {
        material->SetMainTexture(texture);
    }

    Build();
}

void RawImage::Update() {
    if (!isReady()) return;

    Build();
}

void RawImage::Render() {
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

void RawImage::OnDestroy() {
    if (!isReady()) return;

    VAO->Leave();
    material->shader->Leave();
    material->shader->exit();
    delete (material);
    material = nullptr;
}

RawImage* RawImage::Build() {
    Rect rect = entity->transform->rectTransform->rect;

    GLfloat wX = rect.width / 2;
    GLfloat wY = rect.height / 2;

    vertices.clear();
    vertices = {
        {-wX, -wY, 0.0f},  // Bottom-left
        {wX, -wY, 0.0f},  // Bottom-right
        {wX, wY, 0.0f},  // Top-right
        {-wX, wY, 0.0f}  // Top-left
    };

    VAO->Use();
    VAO->Load<glm::vec3>(Vbo::VERTICES, vertices);
    VAO->Load<glm::vec2>(Vbo::UV, uv);
    VAO->Load<glm::vec3>(Vbo::NORMALS, normals);
    VAO->Load<GLushort>(Vbo::INDEXES, indexes);
    VAO->Leave();

    return this;
}
}  // namespace se
