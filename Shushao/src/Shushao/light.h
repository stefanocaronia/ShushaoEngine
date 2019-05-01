#pragma once

#include "Core.h"

#include "color.h"
#include "component.h"

namespace se {

struct SHUSHAO_API Attenuation {
    GLfloat constant;
    GLfloat linear;
    GLfloat quadratic;
};

struct SHUSHAO_API UniformLight {
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    GLfloat constant;
    GLfloat linear;
    GLfloat quadratic;
    GLfloat cutoff;
};

class SHUSHAO_API Light : public Component {
public:
    enum class Type {
        SPOT,
        DIRECTIONAL,
        POINT,
        RECTANGLE,
        DISC
    };

    virtual void setup() { name = "Light"; }

    bool enabled;
    Light::Type type = Light::Type::POINT;
    glm::vec3 direction;
    Color ambient = color::white;
    Color diffuse = color::white;
    Color specular = color::white;
    Attenuation attenuation{1.0f, 1.0f, 1.0f};
    float cutoff;

    std::string GetTypeDesc();
    UniformLight GetUniform();

    void Copy(Light* other);

protected:
    void Update();
    void Render();
};

}  // namespace se
