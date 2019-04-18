#include <math_.h>

#include "debug.h"
#include "shaders/shader.h"
#include "vbo.h"

namespace se {

const std::string Vbo::VERTICES = "vertices";
const std::string Vbo::NORMALS = "normals";
const std::string Vbo::INDEXES = "indexes";
const std::string Vbo::COLORS = "colors";
const std::string Vbo::SIZES = "sizes";
const std::string Vbo::UV = "uv";

VboConfiguration VBO_CONFIG_VERTEX = {
    GL_ARRAY_BUFFER,
    ShaderLocation::LOCATION_POSITION,
    3, GL_FLOAT, GL_FALSE, 0, (void*)0,
    GL_STATIC_DRAW  //
};

VboConfiguration VBO_CONFIG_NORMAL = {
    GL_ARRAY_BUFFER,
    ShaderLocation::LOCATION_NORMAL,
    3, GL_FLOAT, GL_FALSE, 0, (void*)0,
    GL_STATIC_DRAW  //
};

VboConfiguration VBO_CONFIG_INDEX = {
    GL_ELEMENT_ARRAY_BUFFER,
    0  //
};

VboConfiguration VBO_CONFIG_COLOR{
    GL_ARRAY_BUFFER,
    ShaderLocation::LOCATION_COLOR,
    4, GL_FLOAT, GL_FALSE, 0, (void*)0,
    GL_STATIC_DRAW  //
};

VboConfiguration VBO_CONFIG_UV{
    GL_ARRAY_BUFFER,
    ShaderLocation::LOCATION_TEXCOORD,
    2, GL_FLOAT, GL_FALSE, 0, (void*)0,
    GL_STATIC_DRAW  //
};

VboConfiguration VBO_CONFIG_FONT{
    GL_ARRAY_BUFFER,
    ShaderLocation::LOCATION_POSITION,
    4, GL_FLOAT, GL_FALSE, 0, (void*)0,
    GL_DYNAMIC_DRAW  //
};

Vbo::~Vbo() {
    Delete();
}

Vbo* Vbo::Init() {
    if (ready) {
        Debug::Log(WARNING) << "Vbo " << name << " already initializated" << std::endl;
        return this;
    }

    glGenBuffers(1, &Id);

    if (config.location > 0) {
        Bind();
        glEnableVertexAttribArray(config.location);
        glVertexAttribPointer(config.location, config.blocksize, config.type, config.normalized, config.stride, config.pointer);
        Unbind();
    }

    ready = true;
    return this;
}

Vbo* Vbo::Delete() {
    glDeleteBuffers(1, &Id);
    return this;
}

Vbo* Vbo::Bind() {
    if (!config.target) {
        Debug::Log(ERROR) << "Can't bind Vbo " << name << ", no target array set" << std::endl;
        exit(1);
        return this;
    }
    glBindBuffer(config.target, Id);
    return this;
}

Vbo* Vbo::Unbind() {
    if (!config.target) {
        Debug::Log(WARNING) << "Can't unbind " << name << ", no target array set" << std::endl;
        return this;
    }
    glBindBuffer(config.target, 0);
    return this;
}
}  // namespace se
