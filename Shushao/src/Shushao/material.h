#pragma once

#include <glad/glad.h>
#include "Shushao/Core.h"
#include "sepch.h"

#include "color.h"
#include "object.h"
#include "shaders/shader.h"
#include "texture.h"

namespace se {

struct SHUSHAO_API ParameterValue {
    GLfloat f = 0;
    GLint i = 0;
    Texture* tex = nullptr;
    glm::mat4 mat{0};
    glm::vec4 vec{0};
    Color col = color::clear;
};

class SHUSHAO_API Parameter {
public:
    Parameter(std::string name_, std::string var_, Uniform* uniform_) : name(name_), var(var_), uniform(uniform_) {
        value.tex = nullptr;
    }

    std::string name;
    std::string var;
    Uniform* uniform;
    ParameterValue value;

    GLfloat GetFloat();
    GLint GetInteger();
    Texture* GetTexture();
    glm::vec4 GetVector();
    glm::mat4 GetMatrix();
    Color GetColor();

    void SetFloat(GLfloat);
    void SetInteger(GLint);
    void SetTexture(Texture*);
    void SetVector(glm::vec4);
    void SetMatrix(glm::mat4);
    void SetColor(Color);
};

class SHUSHAO_API Material : public Object {
public:
    std::map<std::string, Parameter> parameters;

    Material();
    ~Material();

    Color color = color::white;  // The main material's color.
    Texture* mainTexture = nullptr;  // The material's texture.
    glm::vec2 mainTextureOffset;  // The texture offset of the main texture.
    glm::vec2 mainTextureScale;  // The texture scale of the main texture.
    Shader* shader;  // The shader used by the material.

    void init();
    void update();

    void SetShader(Shader*);
    void SetMainTexture(Texture*);
    void AddParameter(std::string, std::string, Uniform*);

    GLfloat GetFloat(std::string var_);
    GLint GetInteger(std::string var_);
    Texture* GetTexture(std::string var_);
    glm::vec4 GetVector(std::string var_);
    glm::mat4 GetMatrix(std::string var_);
    Color GetColor(std::string var_);

    void SetFloat(std::string, GLfloat);
    void SetInteger(std::string, GLint);
    void SetTexture(std::string, Texture*);
    void SetVector(std::string, glm::vec4);
    void SetMatrix(std::string, glm::mat4);
    void SetColor(std::string, Color);

protected:
    // per override
    virtual void Init(){};
    virtual void Update(){};

private:
};

}  // namespace se
