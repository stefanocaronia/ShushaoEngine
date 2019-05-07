#pragma once

#include "../color.h"
#include "../light.h"
#include "../object.h"
#include "Shushao/Core.h"

namespace se {

enum ShaderLocation {
    LOCATION_POSITION = 1,
    LOCATION_TEXCOORD = 2,
    LOCATION_COLOR = 3,
    LOCATION_NORMAL = 4,
    LOCATION_MVP = 5,
    LOCATION_RENDER_COLOR = 6,
    LOCATION_SIZE = 7
};

class SHUSHAO_API Uniform {
public:
    enum class Type {
        FLOAT,
        INTEGER,
        MATRIX,
        VECTOR,
        TEXTURE,
        COLOR,
        LIGHT
    };

    Uniform(std::string name_, std::string var_, Uniform::Type type_, unsigned int location_, bool locked_ = false) : name(name_), var(var_), type(type_), location(location_), locked(locked_) {}

    std::string name;
    std::string var;
    Uniform::Type type;
    unsigned int location = 0;
    bool locked = false;

    // values
    unsigned int texture;

    void SetFloat(GLfloat&);
    void SetInteger(GLint&);
    void SetTextureIndex(GLint&);
    void SetMatrix(GLfloat*);
    void SetVector(glm::vec2&);
    void SetVector(glm::vec3&);
    void SetVector(glm::vec4&);
    void SetColor(Color&);
    void SetLight(UniformLight&);
};

class SHUSHAO_API Shader : public Object {
public:
    std::map<std::string, Uniform> uniforms;

    Shader();
    Shader(std::string);
    Shader(std::string, std::string);
    ~Shader();

    bool inUse = false;

    bool Init();
    void Use();
    void Leave();
    bool Load(std::string);
    void LoadFromString(std::string vsc, std::string fsc, std::string gsc = "");

    void awake();
    void update();
    void exit();

    unsigned int GetProgram();

    void AddUniform(std::string name_, std::string var_, Uniform::Type type_, unsigned int location_ = 0);
    void AddUniform(std::string var_, Uniform::Type type_, unsigned int location_ = 0);
    void AddShaderUniform(std::string var_, Uniform::Type type_, unsigned int location_ = 0);
    void AddShaderUniform(std::string name_, std::string var_, Uniform::Type type_, unsigned int location_ = 0);

    void SetFloat(std::string, GLfloat);
    void SetInteger(std::string, GLint);
    void SetTextureIndex(std::string, GLint);
    void SetMatrix(std::string, GLfloat*);
    void SetVector(std::string, glm::vec2);
    void SetVector(std::string, glm::vec3);
    void SetVector(std::string, glm::vec4);
    void SetColor(std::string, Color);
    void SetLight(std::string, UniformLight&);

    unsigned int GetTextureIndex(std::string);

    void SetMVP(GLfloat*);
    void SetMV(GLfloat*);
    void SetVP(GLfloat*);
    void SetP(GLfloat*);
    void SetV(GLfloat*);
    void SetM(GLfloat*);
    void SetRenderColor(Color);

    void Enable(std::string var);
    void Disable(std::string var);

protected:
    // per override
    virtual void Awake();
    virtual void Update();
    virtual void Exit();

    std::string VertexShaderCode;
    std::string FragmentShaderCode;
    std::string GeometryShaderCode;

private:
    unsigned int programID = 0;

    bool debug = true;

    unsigned int VertexShaderID;
    unsigned int FragmentShaderID;
    unsigned int GeometryShaderID;

    bool loadWithName(std::string, std::string);

    bool compile();
    bool link();

    bool shaderCompilationLog(const unsigned int&);
    bool programCompilationLog(const unsigned int&);
};

}  // namespace se
