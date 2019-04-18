#pragma once

#include "pch/opengl.h"
#include "pch/std.h"

#include "color.h"
#include "debug.h"
#include "object.h"
#include "shaders/shader.h"
#include "vbo.h"

namespace se {

class Vao : public Object {
public:
    Vao();
    ~Vao();

    GLuint Id = 0;  // Vao ID GL
    bool inUse = false;
    bool ready = false;

    std::map<std::string, Vbo*> buffers;

    Vao* Init();
    Vao* Use();
    Vao* Leave();
    Vao* EnablePointers();
    Vao* DisablePointers();

    Vbo* AddBuffer(std::string name_, VboConfiguration config_);
    Vbo* AddBuffer(Vbo* vbo);
    Vbo* GetBuffer(std::string name);

    template <class T>
    Vao* Load(std::string name_, std::vector<T>& elements) {
        if (!inUse) {
            Debug::Log(ERROR) << "VAO is not in use" << std::endl;
            return this;
        }

        auto it = buffers.find(name_);
        if (it == buffers.end()) {
            Debug::Log(ERROR) << "VBO " << name_ << " not found" << std::endl;
            return this;
        }

        if (!buffers[name_]->ready) {
            buffers[name_]->Init();
        }

        buffers[name_]->Load<T>(elements);

        return this;
    }
};

}  // namespace se
