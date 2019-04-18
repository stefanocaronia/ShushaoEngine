#pragma once

#include <math_.h>
#include <std_.h>

#include "color.h"
#include "design.h"
#include "globals.h"
#include "renderer.h"
#include "vao.h"

namespace se {

class Shader;

class GeometryRenderer : public Renderer {
public:
    virtual void setup();

    ~GeometryRenderer();

    Vao* VAO;
    Shader* shader;

    RenderMode renderMode = RenderMode::WORLD;

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec4> colors;

    void AddLine(glm::vec3, glm::vec3, Color);
    void AddPolyline(std::vector<glm::vec3>, Color);
    void AddCircle(glm::vec3, float, Color, DrawMode);

    void Awake();
    void Update();
    void Render();
    void OnDestroy();
};

}  // namespace se
