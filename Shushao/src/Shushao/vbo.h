#pragma once

#include <glad/glad.h>

#include "Shushao/Core.h"
#include "sepch.h"

#include "object.h"

namespace se {

class SHUSHAO_API VboConfiguration {
public:
    VboConfiguration(
        GLenum target_ = GL_ARRAY_BUFFER,
        GLuint location_ = 0,
        GLint blocksize_ = 3,
        GLenum type_ = GL_FLOAT,
        GLboolean normalized_ = GL_FALSE,
        GLsizei stride_ = 0,
        const GLvoid* pointer_ = (void*)0,
        GLenum usage_ = GL_STATIC_DRAW) {
        target = target_;
        location = location_;
        blocksize = blocksize_;
        type = type_;
        normalized = normalized_;
        stride = stride_;
        pointer = pointer_;
        usage = usage_;
    }

    GLenum target = GL_ARRAY_BUFFER;
    GLuint location = 0;
    GLint blocksize = 3;
    GLenum type = GL_FLOAT;
    GLboolean normalized = GL_FALSE;
    GLsizei stride = 0;
    const GLvoid* pointer = (void*)0;
    GLenum usage = GL_STATIC_DRAW;
};

extern VboConfiguration VBO_CONFIG_VERTEX;
extern VboConfiguration VBO_CONFIG_INDEX;
extern VboConfiguration VBO_CONFIG_NORMAL;
extern VboConfiguration VBO_CONFIG_COLOR;
extern VboConfiguration VBO_CONFIG_UV;
extern VboConfiguration VBO_CONFIG_FONT;

class SHUSHAO_API Vbo : public Object {
public:
    static const std::string VERTICES;
    static const std::string NORMALS;
    static const std::string INDEXES;
    static const std::string COLORS;
    static const std::string SIZES;
    static const std::string UV;

    Vbo(VboConfiguration config_) : config(config_) {}
    ~Vbo();

    GLuint Id = 0;  // Vbo ID GL
    GLsizeiptr buffersize = 0;
    GLuint size = 0;
    bool ready = false;

    VboConfiguration config;

    Vbo* Init();
    Vbo* Delete();
    Vbo* Bind();
    Vbo* Unbind();

    template <class T>
    Vbo* Load(std::vector<T>& elements) {
        if (!ready) {
            return this;
        }
        Bind();
        GLsizeiptr oldsize = buffersize;
        size = elements.size();
        buffersize = elements.size() * sizeof(T);
        if (oldsize == buffersize) {
            glBufferSubData(config.target, 0, buffersize, &elements[0]);
        } else {
            glBufferData(config.target, buffersize, &elements[0], config.usage);
        }
        Unbind();
        return this;
    }
};
}  // namespace se
