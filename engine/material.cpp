#include "material.h"
#include "debug.h"

namespace se {

	using namespace std;

	//{ #region parameter

	GLfloat Parameter::GetFloat() {
		return value.f;
	}

	GLint Parameter::GetInteger() {
		return value.i;
	}

	Texture* Parameter::GetTexture() {
		return value.tex;
	}

	glm::vec4 Parameter::GetVector() {
		return value.vec;
	}

	glm::mat4 Parameter::GetMatrix() {
		return value.mat;
	}

	Color Parameter::GetColor() {
		return value.col;
	}

	void Parameter::SetFloat(GLfloat value_) {
		value.f = value_;
	}

	void Parameter::SetInteger(GLint value_) {
		value.i = value_;
	}

	void Parameter::SetTexture(Texture* value_) {
		value.tex = value_;
	}

	void Parameter::SetVector(glm::vec4 value_) {
		value.vec = value_;
	}

	void Parameter::SetMatrix(glm::mat4 value_) {
		value.mat = value_;
	}

	void Parameter::SetColor(Color value_) {
		value.col = value_;
	}

	//}

	Material::Material() {}

	Material::~Material(){
		parameters.clear();
	}

	void Material::SetShader(Shader* shader_) {
		shader = shader_;
        Init();
	}

	void Material::SetMainTexture(Texture* texture_) {
		mainTexture = texture_;
		SetTexture("main_texture", mainTexture);
	}

	void Material::AddParameter(string name_, string var_, Uniform* uniform_) {
		parameters.insert(pair<string, Parameter>(var_, { name_, var_, uniform_ }));
	}

	void Material::init() {

		if (shader == nullptr) {
			Debug::Log(ERROR) << "Shader not loaded" << endl;
		}

		parameters.clear();

		shader->awake();

		for (auto &it : shader->uniforms) {
			AddParameter(it.second.name, it.first, &it.second);
		}

		Init();
	}

	void Material::update() {

		if (!shader->inUse) shader->Use();
		shader->update();

		for (const auto& it : parameters) {
			Parameter parameter = it.second;
			if (parameter.uniform->locked ||
				parameter.uniform->location == ShaderLocation::LOCATION_MAIN_TEXTURE ||
				parameter.uniform->location == ShaderLocation::LOCATION_RENDER_COLOR ||
				parameter.uniform->location == ShaderLocation::LOCATION_MVP) {
				continue;
			}
			switch (parameter.uniform->type) {
				case UniformType::INTEGER:
					parameter.uniform->SetInteger(parameter.value.i);
					break;
				case UniformType::TEXTURE:
					glActiveTexture(parameter.uniform->texture);
					glBindTexture(GL_TEXTURE_2D, parameter.value.tex->TextureID);
					break;
				case UniformType::FLOAT:
					parameter.uniform->SetFloat(parameter.value.f);
					break;
				case UniformType::MATRIX:
					parameter.uniform->SetMatrix(&parameter.value.mat[0][0]);
					break;
				case UniformType::VECTOR:
					parameter.uniform->SetVector(parameter.value.vec);
					break;
				case UniformType::COLOR:
					parameter.uniform->SetColor(parameter.value.col);
					break;
			}

		}

		Update();
	}

	//{ #region getters/setters values

	GLfloat Material::GetFloat(std::string var_) {
		const auto& it = parameters.find(var_);
		if (it != parameters.end())
			return it->second.value.f;
		return 0.0f;
	}

	GLint Material::GetInteger(std::string var_) {
		const auto& it = parameters.find(var_);
		if (it != parameters.end())
			return it->second.value.i;
		return 0;
	}

	Texture* Material::GetTexture(std::string var_) {
		const auto& it = parameters.find(var_);
		if (it != parameters.end())
			return it->second.value.tex;
		return nullptr;
	}

	glm::vec4 Material::GetVector(std::string var_) {
		const auto& it = parameters.find(var_);
		if (it != parameters.end())
			return it->second.value.vec;
		return {0, 0, 0, 0};
	}

	glm::mat4 Material::GetMatrix(std::string var_) {
		const auto& it = parameters.find(var_);
		if (it != parameters.end())
			return it->second.value.mat;
		glm::mat4 m;
		return m;
	}

	Color Material::GetColor(std::string var_) {
		const auto& it = parameters.find(var_);
		if (it != parameters.end())
			return it->second.value.col;
		return Color::clear;
	}

	void Material::SetFloat(std::string var_, GLfloat value_) {
		auto it = parameters.find(var_);
		if (it != parameters.end())
			it->second.value.f = value_;
	}

	void Material::SetInteger(std::string var_, GLint value_) {
		auto it = parameters.find(var_);
		if (it != parameters.end())
			it->second.value.i = value_;
	}

	void Material::SetTexture(std::string var_, Texture* value_) {
		auto it = parameters.find(var_);
		if (it != parameters.end())
			it->second.value.tex = value_;
	}

	void Material::SetVector(std::string var_, glm::vec4 value_) {
		auto it = parameters.find(var_);
		if (it != parameters.end())
			it->second.value.vec = value_;
	}

	void Material::SetMatrix(std::string var_, glm::mat4 value_) {
		auto it = parameters.find(var_);
		if (it != parameters.end())
			it->second.value.mat = value_;
	}

	void Material::SetColor(std::string var_, Color value_) {
		auto it = parameters.find(var_);
		if (it != parameters.end())
			it->second.value.col = value_;
	}

	//}

}
