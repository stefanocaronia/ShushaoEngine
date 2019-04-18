#include <math_.h>

#include "debug.h"
#include "vao.h"

namespace se {

Vao::Vao() {
    name = "Vao";
}

Vao::~Vao() {
    for (auto& it : buffers) {
        if (it.second != nullptr) {
            Debug::Log << "Cancello buffer" << it.second->name << std::endl;  //<< " (" + util::classtitle(typeid(*it.second).name()) +")"
            delete (it.second);
            it.second = nullptr;
        }
    }

    buffers.clear();

    glDeleteVertexArrays(1, &Id);
}

Vbo* Vao::AddBuffer(const std::string name_, VboConfiguration config_) {
    Vbo* buff = new Vbo(config_);
    buff->name = name_;
    AddBuffer(buff);
    return buffers[name_];
}

Vbo* Vao::AddBuffer(Vbo* vbo_) {
    buffers[vbo_->name] = vbo_;
    return vbo_;
}

Vbo* Vao::GetBuffer(const std::string name_) {
    auto it = buffers.find(name_);
    if (it == buffers.end()) return nullptr;
    return (Vbo*)buffers[name_];
}

Vao* Vao::Use() {
    if (!Id) {
        Debug::Log(ERROR) << "VAO not initializated" << std::endl;
    }
    glBindVertexArray(Id);
    EnablePointers();
    inUse = true;
    return this;
}

Vao* Vao::Leave() {
    glBindVertexArray(0);
    DisablePointers();
    inUse = false;
    return this;
}

Vao* Vao::EnablePointers() {
    for (auto& it : buffers) {
        glEnableVertexAttribArray(it.second->config.location);
    }
    return this;
}

Vao* Vao::DisablePointers() {
    for (auto& it : buffers) {
        glDisableVertexAttribArray(it.second->config.location);
    }
    return this;
}

Vao* Vao::Init() {
    if (ready) return this;
    glGenVertexArrays(1, &Id);

    Use();
    for (auto& it : buffers) {
        if (it.second != nullptr && !it.second->ready) {
            (Vbo*)it.second->Init();
        }
    }
    Leave();

    ready = (Id > 0);
    return this;
}
}  // namespace se
