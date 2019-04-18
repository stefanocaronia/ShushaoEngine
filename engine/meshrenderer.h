#pragma once

#include <math_.h>

#include "color.h"
#include "material.h"
#include "mesh.h"
#include "renderer.h"
#include "shaders/shader.h"

namespace se {

class MeshRenderer : public Renderer {
public:
    virtual void setup();
    ~MeshRenderer();

    bool isReady();

    Mesh* mesh = nullptr;
    Material* material = nullptr;

    MeshRenderer* SetMesh(Mesh* mesh_) {
        mesh = mesh_;
        return this;
    }

    MeshRenderer* SetMaterial(Material* material_) {
        material = material_;
        return this;
    }

protected:
    void Awake();
    void Update();
    void Render();
    void OnDestroy();

private:
};

}  // namespace se
